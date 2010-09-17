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

#ifndef INTERFACE_APPPROJECTWIZARD_QTLAYERLISTWIDGET_H
#define INTERFACE_APPPROJECTWIZARD_QTLAYERLISTWIDGET_H

// QT Includes
#include <QWidget>

// Boost includes
#include <boost/shared_ptr.hpp>

namespace Seg3D 
{

class QtLayerListWidgetPrivate;
typedef boost::shared_ptr< QtLayerListWidgetPrivate > QtLayerListWidgetPrivateHandle;

// Class definition
class QtLayerListWidget : public QWidget
{
Q_OBJECT
Q_SIGNALS:
	void index_changed_signal();

// -- constructor/destructor --
public:
    QtLayerListWidget( QWidget* parent = 0 );
    virtual ~QtLayerListWidget();
    
public:
	int get_value();
	QString get_label() const;
	bool counter_hidden();
	void set_validity( bool valid );
	void set_mask_name( const std::string& name );
	void set_mask_index( const int index );
	void hide_counter( bool hide );

private Q_SLOTS:
	void emit_changed_signal( int );
    

// -- widget internals -- 
private:
    QtLayerListWidgetPrivateHandle private_;
    
};

}  // end namespace QtUtils

#endif
