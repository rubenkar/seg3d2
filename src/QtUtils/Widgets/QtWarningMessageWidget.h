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

#ifndef QTUTILS_WIDGETS_QTWARNINGMESSAGEWIDGET_H
#define QTUTILS_WIDGETS_QTWARNINGMESSAGEWIDGET_H

// Boost includes
#include <boost/shared_ptr.hpp>

// QT includes
#include <QtGui/QWidget>

namespace QtUtils
{
	
class QtWarningMessageWidgetPrivate;
	
class QtWarningMessageWidget : public QWidget
{
Q_OBJECT
	
public:
	// - Constructor / Destructor
	QtWarningMessageWidget( QWidget *parent = 0 );
	virtual ~QtWarningMessageWidget();
	
public:
	void set_warning_message( const std::string& warning );
	virtual void setVisible( bool visible );
	
private:
	
	virtual void hide();
	
	virtual void show();
	
private Q_SLOTS:
	void set_hidden();
	void set_shown();
	
private:
	boost::shared_ptr< QtWarningMessageWidgetPrivate > private_;
	
};
	
} // end namespace QtUtils

#endif
