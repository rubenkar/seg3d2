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

#ifndef APPLICATION_TOOLS_DISCRETEGAUSSIANFILTER_H
#define APPLICATION_TOOLS_DISCRETEGAUSSIANFILTER_H

#include <Application/Tool/SingleTargetTool.h>

namespace Seg3D
{

class DiscreteGaussianFilter : public SingleTargetTool
{
SEG3D_TOOL(
SEG3D_TOOL_NAME( "DiscreteGaussianFilter", "Filter for smoothing data" )
SEG3D_TOOL_MENULABEL( "Gaussian Blur" )
SEG3D_TOOL_MENU( "Data Filters" )
SEG3D_TOOL_SHORTCUT_KEY( "CTRL+ALT+D" )
SEG3D_TOOL_URL( "http://www.sci.utah.edu/SCIRunDocs/index.php/CIBC:Seg3D2:DiscreteGaussianBlur:1" )
SEG3D_TOOL_VERSION( "1" )
)

public:
	DiscreteGaussianFilter( const std::string& toolid );
	virtual ~DiscreteGaussianFilter();
	
private:
	// -- handle updates from layermanager --
	void handle_layers_changed();

	// -- state --
public:
	/// Whether the layer needs to be replaced
	Core::StateBoolHandle replace_state_;
	
	/// Whether the data format needs to be preserved in the filter
	Core::StateBoolHandle preserve_data_format_state_;

	/// Blurring distance
	Core::StateRangedDoubleHandle blurring_distance_state_;

	// -- execute --
public:
	/// Execute the tool and dispatch the action
	virtual void execute( Core::ActionContextHandle context );
	
};

} // end namespace

#endif
