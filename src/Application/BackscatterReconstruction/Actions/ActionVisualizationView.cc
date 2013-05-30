/*
 For more information, please see: http://software.sci.utah.edu
 
 The MIT License
 
 Copyright (c) 2013 Scientific Computing and Imaging Institute,
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

#include <Core/Action/ActionDispatcher.h>
#include <Core/Action/ActionFactory.h>
#include <Core/State/Actions/ActionSet.h>

// Application Includes
#include <Application/BackscatterReconstruction/Actions/ActionVisualizationView.h>

#include <Application/ToolManager/ToolManager.h>
#include <Application/ToolManager/Actions/ActionOpenTool.h>
#include <Application/ToolManager/Actions/ActionActivateTool.h>

#include <Application/ViewerManager/ViewerManager.h>

// REGISTER ACTION:
// Define a function that registers the action. The action also needs to be
// registered in the CMake file.
CORE_REGISTER_ACTION( Seg3D, VisualizationView )

namespace Seg3D
{
  
bool ActionVisualizationView::validate( Core::ActionContextHandle& context )
{
  return true; // validated
}

bool ActionVisualizationView::run( Core::ActionContextHandle& context,
                                   Core::ActionResultHandle& result )
{
  ToolManager::tool_list_type openTools = ToolManager::Instance()->tool_list();
  ToolManager::tool_list_type::iterator it = openTools.begin();
  ToolManager::tool_list_type::iterator itEnd = openTools.end();
  bool toolFound = false;
  while ( it != itEnd )
  {
    std::string toolid = it->first;
    std::size_t pos = toolid.find_last_of("_");
    if (pos != std::string::npos)
    {
      if ( toolid.substr(0, pos) == "viewertool")
      {
        ActionActivateTool::Dispatch( Core::Interface::GetWidgetActionContext(), toolid );
        toolFound = true;
        break;
      }
    }
    ++it;
  }
  
  if (! toolFound)
    ActionOpenTool::Dispatch( Core::Interface::GetWidgetActionContext(), "viewertool" );
  
  return true;
}

void ActionVisualizationView::Dispatch( Core::ActionContextHandle context )
{
  ActionVisualizationView* action = new ActionVisualizationView;
  Core::ActionDispatcher::PostAction( Core::ActionHandle( action ), context );
}
  
} // end namespace Seg3D
