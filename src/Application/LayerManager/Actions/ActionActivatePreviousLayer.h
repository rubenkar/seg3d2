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

#ifndef APPLICATION_LAYERMANAGER_ACTIONS_ACTIONACTIVATEPREVIOUSLAYER_H
#define APPLICATION_LAYERMANAGER_ACTIONS_ACTIONACTIVATEPREVIOUSLAYER_H

#include <Core/Action/Actions.h>
#include <Core/Interface/Interface.h>

#include <Application/Layer/LayerFWD.h>

namespace Seg3D
{

class ActionActivatePreviousLayer : public Core::Action
{
	
CORE_ACTION(
	CORE_ACTION_TYPE( "ActivatePreviousLayer", "Activate the previous layer.")
	CORE_ACTION_CHANGES_PROJECT_DATA()
)

	// -- Constructor/Destructor --
public:
	ActionActivatePreviousLayer()
	{
	}

	// -- Functions that describe action --
public:
	virtual bool validate( Core::ActionContextHandle& context );
	virtual bool run( Core::ActionContextHandle& context, Core::ActionResultHandle& result );
	
	// -- Dispatch this action from the interface --
public:
	
	// DISPATCH:
	// Dispatch an action that activates a layer
	static void Dispatch( Core::ActionContextHandle context );
};

} // end namespace Seg3D

#endif
