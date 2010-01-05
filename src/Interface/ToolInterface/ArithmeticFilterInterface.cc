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

#include <Interface/ToolInterface/ArithmeticFilterInterface.h>
#include "ui_ArithmeticFilterInterface.h"

namespace Seg3D {
  
SCI_REGISTER_TOOLINTERFACE(ArithmeticFilterInterface)


class ArithmeticFilterInterfacePrivate {
public:
  Ui::ArithmeticFilterInterface ui_;
};


ArithmeticFilterInterface::ArithmeticFilterInterface() :
private_(new ArithmeticFilterInterfacePrivate)
{  
  
}

ArithmeticFilterInterface::~ArithmeticFilterInterface()
{
}


bool
ArithmeticFilterInterface::build_widget(QFrame* frame)
{
  
  private_->ui_.setupUi(frame);
  
  //varianceAdjuster = new SliderSpinCombo();
//    private_->ui_.varianceHLayout_bottom->addWidget(varianceAdjuster);
//    
//    kernelWidthAdjuster = new SliderSpinCombo();
//    private_->ui_.kernelHLayout_bottom->addWidget(kernelWidthAdjuster);
  
  
  makeConnections();
  SCI_LOG_DEBUG("Finished building an Arithmetic Filter Interface");
  
  return (true);
}

void 
ArithmeticFilterInterface::makeConnections()
{
}

//  --- Private slots for custom signals ---  //
void ArithmeticFilterInterface::senseVolumeAChanged(int active)
{
  Q_EMIT volumeAChanged( active );
}

void ArithmeticFilterInterface::senseVolumeBChanged(int active)
{
  Q_EMIT volumeBChanged( active );
}

void ArithmeticFilterInterface::senseVolumeCChanged(int active)
{
  Q_EMIT volumeCChanged( active );
}


void ArithmeticFilterInterface::senseFilterRun()
{
  if(private_->ui_.replaceCheckBox->isChecked())
  {
    Q_EMIT filterRun(true);
  }
  else
  {
    Q_EMIT filterRun(false);
  }
}
  
//  --- Public slots for setting widget values ---  //
void ArithmeticFilterInterface::setVolumeA(int active)
{
  private_->ui_.volumeAComboBox->setCurrentIndex(active);
}

void ArithmeticFilterInterface::addToVolumeA(QStringList &items)
{
  private_->ui_.volumeAComboBox->addItems(items);
}
  
void ArithmeticFilterInterface::setVolumeB(int active)
{
  private_->ui_.volumeBComboBox->setCurrentIndex(active);
}

void ArithmeticFilterInterface::addToVolumeB(QStringList &items)
{
  private_->ui_.volumeBComboBox->addItems(items);
}

void ArithmeticFilterInterface::setVolumeC(int active)
{
  private_->ui_.volumeCComboBox->setCurrentIndex(active);
}

void ArithmeticFilterInterface::addToVolumeC(QStringList &items)
{
  private_->ui_.volumeCComboBox->addItems(items);
}
  
void ArithmeticFilterInterface::addToSampleExpressions(QStringList &items)
{
  private_->ui_.comboBox->addItems(items);
}

void ArithmeticFilterInterface::addToExpressions(QStringList &items)
{
  //private_->ui_.comboBox->addItems(items);
}
  
  
  
} //end seg3d
