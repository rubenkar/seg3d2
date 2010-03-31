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

#include <Application/LayerManager/LayerManager.h>
#include <Application/LayerManager/Actions/ActionActivateLayer.h>

namespace Seg3D
{

// REGISTER ACTION:
// Define a function that registers the action. The action also needs to be
// registered in the CMake file.
SCI_REGISTER_ACTION(ActivateLayer);

bool ActionActivateLayer::validate( ActionContextHandle& context )
{
    if ( this->layer_handle_ )
	{
		return true;
	}		
	
	if ( !( StateEngine::Instance()->is_statealias( this->layer_name_.value() ) ) )
	{
		context->report_error( std::string( "LayerName: '" ) + this->layer_name_.value() + "' is invalid" );
		return false;
	}

	return true; // validated
}

	bool ActionActivateLayer::run( ActionContextHandle& context, ActionResultHandle& result )
	{
		if( this->layer_handle_ )
		{
			LayerManager::Instance()->set_active_layer( layer_handle_ );
			return true;
		}
		
		if( StateEngine::Instance()->is_statealias( this->layer_name_.value() ) )
		{
			LayerManager::Instance()->set_active_layer( 
				LayerManager::Instance()->get_LayerHandle_from_layer_name( this->layer_name_.value() ) );
			return true;
		}
		return false;
	}

	ActionHandle ActionActivateLayer::Create( const LayerHandle layer )
	{
		ActionActivateLayer* action = new ActionActivateLayer;
		action->layer_handle_ = layer;
		action->layer_name_ = layer->name_state_->get();
		
		return ActionHandle( action );
	}
	
	void ActionActivateLayer::Dispatch( const LayerHandle layer )
	{
		Interface::PostAction( Create( layer ) );
	}

	
	
	//void ActionActivateLayer::Dispatch( const std::string& layer_name )
	//{
	//	ActionActivateLayer* action = new ActionActivateLayer;
	//	action->layer_handle_ = LayerManager::Instance()->get_LayerHandle_from_layer_name( layer_name );
	//	action->layer_name_.value() = layer_name;

	//	Interface::PostAction( ActionHandle( action ) );
	//}
	
	

} // end namespace Seg3D
