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

#ifndef QTUTILS_BRIDGE_DETAIL_QTACTIONCONNECTOR_H
#define QTUTILS_BRIDGE_DETAIL_QTACTIONCONNECTOR_H

#include <QAction>
#include <QPointer>

#include <Core/State/StateValue.h>

#include <QtUtils/Bridge/detail/QtConnectorBase.h>

namespace QtUtils
{

class QtActionConnector : public QtConnectorBase
{
	Q_OBJECT

public:
	QtActionConnector( QAction* parent, Core::StateBoolHandle& state,
		bool blocking = true );
	QtActionConnector( QAction* parent, boost::function< void() > func );

	virtual ~QtActionConnector();

	// -- slot functions for boost signals --
private:
	static void SetActionChecked( QPointer< QtActionConnector > qpointer,
		bool checked, Core::ActionSource source );

	// -- slot functions for Qt signals --
private Q_SLOTS:
	void set_state( bool value );
	void call_func();

private:
	QAction* parent_;
	Core::StateBoolHandle state_;
	boost::function< void () > func_;
};

}

#endif