# This variable will help provide a master list of all the sources.
# Add new source files here.
SET(UNRRDU_SOURCES
  1op.c
  2op.c
  3op.c
  about.c
  axdelete.c
  axinfo.c
  axinsert.c
  axmerge.c
  axsplit.c
  block.c
  ccadj.c
  ccfind.c
  ccmerge.c
  ccsettle.c
  cmedian.c
  convert.c
  crop.c
  data.c
  dhisto.c
  dice.c
  dist.c
  env.c
  flip.c
  flotsam.c
  gamma.c
  head.c
  heq.c
  histax.c
  histo.c
  imap.c
  inset.c
  jhisto.c
  join.c
  lut.c
  lut2.c
  make.c
  minmax.c
  mlut.c
  mrmap.c
  pad.c
  permute.c
  privateUnrrdu.h
  project.c
  quantize.c
  resample.c
  reshape.c
  rmap.c
  save.c
  shuffle.c
  slice.c
  splice.c
  subst.c
  swap.c
  tile.c
  unblock.c
  unorient.c
  unquantize.c
  unrrdu.h
  untile.c
  )

ADD_TEEM_LIBRARY(unrrdu ${UNRRDU_SOURCES})
