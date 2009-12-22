/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2009 Scientific Computing and Imaging Institute,
   University of Utah.

   
   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

#ifndef APPLICATION_VIEW_VIEW_H
#define APPLICATION_VIEW_VIEW_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// STL includes
#include <vector>

// Boost includes 
#include <boost/shared_ptr.hpp>

// Application includes
#include <Application/View/ViewRenderer.h>

namespace Seg3D {

// Forward declarations
class View;
typedef boost::shared_ptr<View> ViewHandle;


// Class declarations

class View {

// -- types of views --
  public:
    enum view_type {
      AXIAL_E = 0,
      SAGITTAL_E,
      CORONAL_E,
      VOLUME_E
    };

// -- constructor/destructor --
  public:
    View();
    virtual ~View();

    view_type type() const { return type_; }
    void      set_type(view_type new_type) { type_ = new_type; }

  private:
    // Type of the view
    view_type type_;

// -- Renderer information --

  // Note: by default a dummy renderer is generated.
  public:
    
    ViewRendererHandle renderer() { return renderer_; }
    void set_renderer(ViewRendererHandle renderer) { renderer_ = renderer; }

  private:
    ViewRendererHandle renderer_;
};

} // end namespace Seg3D

#endif
