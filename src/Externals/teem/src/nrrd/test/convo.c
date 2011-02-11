/*
  Teem: Tools to process and visualize scientific data and images              
  Copyright (C) 2008, 2007, 2006, 2005  Gordon Kindlmann
  Copyright (C) 2004, 2003, 2002, 2001, 2000, 1999, 1998  University of Utah

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public License
  (LGPL) as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  The terms of redistributing and/or modifying this software also
  include exceptions to the LGPL that facilitate static linking.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this library; if not, write to Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <math.h>
#include "../nrrd.h"

char *convoInfo = ("Good for convolution of two 2-D nrrd, and nothing else.");

#define CONVO "convo"

int
convoFunc(Nrrd *nout, Nrrd *_nimg, Nrrd *_nmask, int renorm, int crop) {
  char me[]="convoFunc", err[AIR_STRLEN_MED];
  Nrrd *nimg, *nmask, *npad;
  airArray *mop;
  int E;
  unsigned int i;
  int x, y,
    ix, iy,         /* image coordinates */
    isx, isy,       /* input image size */
    osx, osy,       /* output image size */
    mx, my,         /* mask coordinates */
    msx, msy,       /* mask size */
    lox, hix,       /* amount of padding along X caused by mask */
    loy, hiy;       /* amount of padding along Y caused by mask */
  size_t cmin[2], cmax[2];    /* cropping bounds */
  ptrdiff_t pmin[2], pmax[2]; /* cropping bounds */
  float *ohere, *idata, *mdata, *odata, sum;

  isx = _nimg->axis[0].size;
  isy = _nimg->axis[1].size;
  msx = _nmask->axis[0].size;
  msy = _nmask->axis[1].size;
  lox = (msx-1)/2;
  hix = msx/2;
  loy = (msy-1)/2;
  hiy = msy/2;
  osx = isx + lox + hix;
  osy = isy + loy + hiy;

  pmin[0] = -lox;
  pmin[1] = -loy;
  pmax[0] = isx - 1 + hix;
  pmax[1] = isy - 1 + hiy;
  /*
  fprintf(stderr, "%s: lox,loy = %d,%d   hix,hiy = %d,%d\n",
          me, lox, loy, hix, hiy);
  fprintf(stderr, "%s: min[] = %d,%d    max[] = %d,%d\n",
          me, min[0], min[1], max[0], max[1]);
  */

  mop = airMopNew();
  airMopAdd(mop, nimg=nrrdNew(), (airMopper)nrrdNuke, airMopAlways);
  airMopAdd(mop, nmask=nrrdNew(), (airMopper)nrrdNuke, airMopAlways);
  airMopAdd(mop, npad=nrrdNew(), (airMopper)nrrdNuke, airMopAlways);
  E = 0;
  if (!E) E |= nrrdConvert(nimg, _nimg, nrrdTypeFloat);
  if (!E) E |= nrrdConvert(nmask, _nmask, nrrdTypeFloat);
  /* we will blow away the values values generated by this; padding here
     is just a simple way of creating a nrrd with the correct dimensions */
  if (!E) E |= nrrdPad_va(npad, nimg, pmin, pmax, nrrdBoundaryPad, 0.0);
  if (E) {
    sprintf(err, "%s: set-up problem", me);
    biffMove(CONVO, me, NRRD); airMopError(mop); return 1;
  }
  idata = (float *)nimg->data;
  mdata = (float *)nmask->data;
  odata = (float *)npad->data;
  for (i=0; i<nrrdElementNumber(npad); i++) {
    odata[i] = 0.0;
  }
  
  if (renorm) {
    sum = 0;
    for (i=0; i<nrrdElementNumber(nmask); i++) {
      sum += mdata[i];
    }
    if (sum) {
      for (i=0; i<nrrdElementNumber(nmask); i++) {
        mdata[i] /= sum;
      }
    }
  }

  /*
  for (iy=0; iy<isy; iy++) {
    for (ix=0; ix<isx; ix++) {
      ohere = odata + ix+lox + osx*(iy+loy);
      ihere = idata + ix + isx*iy;
      for (my=-loy; my<=hiy; my++) {
        for (mx=-lox; mx<=hix; mx++) {
          ohere[mx+osx*my] += mdata[mx+lox + msx*(my+loy)]*ihere[mx+isx*my];
          if (10 == iy && 10 == ix) {
            fprintf(stderr, "mdata[%d,%d] = mdata[%d] = %g\n",
                    mx, my, mx+lox + msx*(my+loy), 
                    mdata[mx+lox + msx*(my+loy)]);
          }
        }
      }
    }
  }
  */
  for (iy=0; iy<osy; iy++) {
    for (ix=0; ix<osx; ix++) {
      ohere = odata + ix + osx*iy;
      for (my=-loy; my<=hiy; my++) {
        y = iy + my - loy;
        if (!AIR_IN_CL(0, y, isy-1))
          continue;
        for (mx=-lox; mx<=hix; mx++) {
          x = ix + mx - lox;
          if (!AIR_IN_CL(0, x, isx-1))
            continue;
          *ohere += mdata[mx+lox + msx*(my+loy)]*idata[x + isx*y];
        }
      }      
    }
  }

  E = 0;
  if (crop) {
    cmin[0] = lox;
    cmin[1] = loy;
    cmax[0] = osx - 1 - hix;
    cmax[1] = osy - 1 - hiy;
    E = nrrdCrop(nout, npad, cmin, cmax);
  } else {
    E = nrrdCopy(nout, npad);
  }
  if (E) {
    sprintf(err, "%s: final crop/copy problem", me);
    biffMove(CONVO, err, NRRD); airMopError(mop); return 1;
  }

  airMopOkay(mop);
  return 0;
}

int
main(int argc, char *argv[]) {
  char *me, *err, *out;
  hestOpt *hopt;
  hestParm *hparm;
  airArray *mop;
  Nrrd *nimg, *nmask, *nout;
  int uncrop, renorm;
  
  me = argv[0];
  mop = airMopNew();
  hparm = hestParmNew();
  hopt = NULL;
  airMopAdd(mop, hparm, (airMopper)hestParmFree, airMopAlways);
  hestOptAdd(&hopt, "c", NULL, airTypeInt, 0, 0, &uncrop, NULL,
             "Don't crop the output image to the dimensions of the input "
             "image.");
  hestOptAdd(&hopt, "r", NULL, airTypeInt, 0, 0, &renorm, NULL,
             "Don't renormalize the weights in the mask to 1.0. ");
  hestOptAdd(&hopt, NULL, "image", airTypeOther, 1, 1, &nimg, NULL,
             "image to operate on", NULL, NULL, nrrdHestNrrd);
  hestOptAdd(&hopt, NULL, "mask", airTypeOther, 1, 1, &nmask, NULL,
             "mask to convolve with", NULL, NULL, nrrdHestNrrd);
  hestOptAdd(&hopt, NULL, "filename", airTypeString, 1, 1, &out, NULL,
             "file to write output nrrd to");
  hestParseOrDie(hopt, argc-1, argv+1, hparm,
                 me, convoInfo, AIR_TRUE, AIR_TRUE, AIR_TRUE);
  airMopAdd(mop, hopt, (airMopper)hestOptFree, airMopAlways);
  airMopAdd(mop, hopt, (airMopper)hestParseFree, airMopAlways);

  nout = nrrdNew();
  airMopAdd(mop, nout, (airMopper)nrrdNuke, airMopAlways);

  if (!( 2 == nimg->dim && 2 == nmask->dim )) {
    fprintf(stderr, "%s: dimension of image (%d) and mask (%d) not both 2\n",
            me, nimg->dim, nmask->dim);
    airMopError(mop); return 1;
  }

  if (convoFunc(nout, nimg, nmask, !renorm, !uncrop)) {
    airMopAdd(mop, err = biffGetDone(CONVO), airFree, airMopAlways);
    fprintf(stderr, "%s: problem save image:\n%s\n", me, err);
    airMopError(mop); return 1;
  }
  if (nrrdSave(out, nout, NULL)) {
    airMopAdd(mop, err = biffGetDone(NRRD), airFree, airMopAlways);
    fprintf(stderr, "%s: problem save image:\n%s\n", me, err);
    airMopError(mop); return 1;
  }

  airMopOkay(mop);
  exit(0);
}
