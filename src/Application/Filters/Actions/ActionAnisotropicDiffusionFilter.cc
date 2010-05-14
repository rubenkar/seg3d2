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
#include <Application/Filters/Actions/ActionAnisotropicDiffusionFilter.h>

// REGISTER ACTION:
// Define a function that registers the action. The action also needs to be
// registered in the CMake file.
CORE_REGISTER_ACTION( Seg3D, AnisotropicDiffusionFilter )

namespace Seg3D
{
	
bool ActionAnisotropicDiffusionFilter::validate( Core::ActionContextHandle& context )
{
	this->layer_.handle() = LayerManager::Instance()->get_layer_by_id( this->layer_id_.value() );

	if ( ! this->layer_.handle() )
	{
		context->report_error( std::string( "LayerID '" ) + this->layer_id_.value() +
			std::string( "' is not valid." ) );
		return false;
	}
	
	if( this->iterations_.value() < 1 )
	{
		context->report_error( "The number of iterations needs to be larger than zero." );
		return false;
	}
	
	if( this->integration_step_.value() < 1 )
	{
		context->report_error( "The integration step needs to be larger than zero." );
		return false;
	}
	
	if( this->conductance_.value() < 0.0 )
	{
		context->report_error( "The conductance needs to be larger than zero." );
		return false;
	}
	
	return true;
}

bool ActionAnisotropicDiffusionFilter::run( Core::ActionContextHandle& context, 
	Core::ActionResultHandle& result )
{
	// TODO: run filter
	context->report_message( std::string( "The AnisotropicDiffusionFilter has been triggered "
		"successfully on layer: " ) + this->layer_.handle()->name_state_->get() );
	return true;
}


Core::ActionHandle ActionAnisotropicDiffusionFilter::Create( std::string layer_id, int iterations, 
	int integration_step, double conductance, bool replace )
{
	// Create a new action
	ActionAnisotropicDiffusionFilter* action = new ActionAnisotropicDiffusionFilter;

	// Setup the parameters
	action->layer_id_.value() = layer_id;
	action->iterations_.value() = iterations;
	action->integration_step_.value() = integration_step;
	action->conductance_.value() = conductance;
	action->replace_.value() = replace;
	
	return ( Core::ActionHandle( action ) );
}

void ActionAnisotropicDiffusionFilter::Dispatch( std::string layer_id, int iterations, 
	int integration_step, double conductance, bool replace )
{	
	Core::Interface::PostAction( Create( layer_id, iterations, integration_step, 
		conductance, replace ) );
}
	
} // end namespace Seg3D
