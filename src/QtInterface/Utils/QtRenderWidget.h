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

#ifndef QTINTERFACE_UTILS_QTRENDERWIDGET_H
#define QTINTERFACE_UTILS_QTRENDERWIDGET_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif 

// Glew includes
// NOTE: Glew needs to be included before any openGL headers
#include <GL/glew.h>

// Qt includes
#include <QtOpenGL>

// Core includes
#include <Core/Utils/ConnectionHandler.h>
#include <Core/RenderResources/RenderResources.h> 
#include <Core/Viewer/AbstractViewer.h>

namespace QtUtils
{

class QtRenderWidget;
class QtRenderWidgetPrivate;
typedef boost::shared_ptr<QtRenderWidgetPrivate> QtRenderWidgetPrivateHandle;

class QtRenderWidget : public QGLWidget, private Core::ConnectionHandler
{
Q_OBJECT

	// -- constructor/ destructor --
public:
	QtRenderWidget( const QGLFormat& format, QWidget* parent, QGLWidget* share, 
		Core::AbstractViewerHandle viewer );
		
	virtual ~QtRenderWidget();

protected:

	// INITIALIZEGL:
	// This function is called by Qt when the widget is initialized
	virtual void initializeGL();
	
	// PAINTGL:
	// This function is called whenever Qt has to repaint the contents of 
	// the widget displaying the Qt scene
	virtual void paintGL();
	
	// RESIZEGL:
	// This function gets called whenever the Qt widget is resized
	virtual void resizeGL( int width, int height );

	// MOUSEDOUBLECLICKEVENT:
	// This function is called by Qt to deliver a double mouse click event
	// to the GUI.
	virtual void mouseDoubleClickEvent( QMouseEvent * event ) {}

	// MOUSEMOVEEVENT:
	// This function is called by Qt to deliver mouse movement event
	// to the GUI.	
	virtual void mouseMoveEvent( QMouseEvent * event );
	
	// MOUSEDOUBLECLICKEVENT:
	// This function is called by Qt to deliver a single mouse click event
	// to the GUI.
	virtual void mousePressEvent( QMouseEvent * event );
	
	// MOUSERELEASEEVENT:
	// This function is called by Qt to deliver a mouse button release event
	// to the GUI.	
	virtual void mouseReleaseEvent( QMouseEvent * event );
	
	// WHEELEVENT:
	// This function is called by Qt to deliver mouse wheel event
	// to the GUI.	
	virtual void wheelEvent( QWheelEvent* event );

	// HIDEEVENT:
	// This function is called by Qt to deliver an event that tells that the
	// widget is being hidden. 
	// NOTE: This is called when the user changes the number of viewers in the
	// main display
	virtual void hideEvent( QHideEvent* event );

	// SHOWEVENT:
	// This function is called by Qt to deliver an event that tells that the
	// widget is being shown
	// NOTE: This is called when the user changes the number of viewers in the
	// main display
	virtual void showEvent( QShowEvent* event );

	// -- internals of the QtRenderWidget --
private:
	QtRenderWidgetPrivateHandle private_;
};

} // end namespace QtUtils

#endif
