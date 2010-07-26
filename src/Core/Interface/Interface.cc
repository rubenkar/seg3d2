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

#include <Core/Interface/Interface.h>

namespace Core
{

CORE_SINGLETON_IMPLEMENTATION( Interface );

class InterfacePrivate
{
public:
	// Handle an action that is generated by a widget
	InterfaceActionContextHandle widget_context_;

	// Handle an action that is generated by the mouse
	InterfaceActionContextHandle mouse_context_;	

	// Handle an action that is generated by the keyboard
	InterfaceActionContextHandle keyboard_context_;	
};

Interface::Interface() :
	private_( new InterfacePrivate)
{
	// Setup different contexts that represent actions from different sources
	this->private_->widget_context_= InterfaceActionContextHandle( new InterfaceActionContext( 
		ActionSource::INTERFACE_WIDGET_E ) );
	this->private_->mouse_context_ = InterfaceActionContextHandle( new InterfaceActionContext( 
		ActionSource::INTERFACE_MOUSE_E ) );
	this->private_->keyboard_context_ = InterfaceActionContextHandle( new InterfaceActionContext( 
		ActionSource::INTERFACE_KEYBOARD_E ) );
}

Interface::~Interface()
{
}

InterfaceActionContextHandle Interface::get_widget_action_context()
{
	return this->private_->widget_context_;
}

InterfaceActionContextHandle Interface::get_mouse_action_context()
{
	return this->private_->mouse_context_;
}

InterfaceActionContextHandle Interface::get_keyboard_action_context()
{
	return this->private_->keyboard_context_;
}
/// -- Static shortcut functions --

void Interface::PostEvent( boost::function< void() > function )
{
	Instance()->post_event( function );
}

void Interface::PostAndWaitEvent( boost::function< void() > function )
{
	Instance()->post_and_wait_event( function );
}

ActionContextHandle Interface::GetWidgetActionContext()
{
	return ActionContextHandle( Interface::Instance()->get_widget_action_context() );
}

ActionContextHandle Interface::GetMouseActionContext()
{
	return ActionContextHandle( Interface::Instance()->get_mouse_action_context() );
}

ActionContextHandle Interface::GetKeyboardActionContext()
{
	return ActionContextHandle( Interface::Instance()->get_keyboard_action_context() );
}

} // end namespace Core
