
#
#  For more information, please see: http://software.sci.utah.edu
# 
#  The MIT License
# 
#  Copyright (c) 2009 Scientific Computing and Imaging Institute,
#  University of Utah.
# 
#  
#  Permission is hereby granted, free of charge, to any person obtaining a
#  copy of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom the
#  Software is furnished to do so, subject to the following conditions:
# 
#  The above copyright notice and this permission notice shall be included
#  in all copies or substantial portions of the Software. 
# 
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
#  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#  DEALINGS IN THE SOFTWARE.
#

##################################################
# Set sources
##################################################

SET(CORE_STATE_SRCS
  StateBase.h
  StateEngine.h
  StateEngine.cc
  StateHandler.h
  StateHandler.cc
  StateIO.h
  StateIO.cc
  StateLabeledOption.h
  StateLabeledOption.cc
  StateName.h
  StateName.cc
  StateOption.cc
  StateOption.h
  StateRangedValue.h
  StateValue.h
  StateViewBase.h
  StateView2D.cc
  StateView2D.h
  StateView3D.cc
  StateView3D.h
  StateVector.h
  State.h
  )

SET(CORE_STATE_ACTIONS_SRCS
  Actions/ActionSet.h
  Actions/ActionSet.cc
  Actions/ActionGet.h
  Actions/ActionGet.cc
  Actions/ActionRotateView3D.h
  Actions/ActionRotateView3D.cc
  Actions/ActionScaleView.h
  Actions/ActionScaleView.cc
  Actions/ActionTranslateView.h
  Actions/ActionTranslateView.cc
  Actions/ActionFlip.h
  Actions/ActionFlip.cc
  Actions/ActionSetRange.h
  Actions/ActionSetRange.cc
  )

CORE_ADD_LIBRARY(Core_State ${CORE_STATE_SRCS} ${CORE_STATE_ACTIONS_SRCS} )
            
TARGET_LINK_LIBRARIES(Core_State
                      Core_Utils
                      Core_Application
                      Core_Interface
                      Core_Action
                      ${SCI_BOOST_LIBRARY})

# Register actions
ADD_LIBRARY_ACTIONS(Core_State
                    ${CORE_STATE_ACTIONS_SRCS})
                    