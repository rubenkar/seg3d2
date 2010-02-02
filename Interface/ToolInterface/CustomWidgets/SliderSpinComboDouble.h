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

#ifndef INTERFACE_TOOLINTERFACE_CUSTOMWIDGETS_SLIDERSPINCOMBODOUBLE_H
#define INTERFACE_TOOLINTERFACE_CUSTOMWIDGETS_SLIDERSPINCOMBODOUBLE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <QtGui>
#include <QWidget>
#include <QtGui/QSlider>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>

namespace Seg3D {

class SliderSpinComboDouble : public QWidget
{
  Q_OBJECT

  Q_SIGNALS:
    void valueAdjusted(double);
    void valueAdjustedContinuously(double);

  public:
    SliderSpinComboDouble(QWidget* parent = 0);
    virtual ~SliderSpinComboDouble();

  public Q_SLOTS:
    void setStep(double);
    void setRanges(double, double);
    void setCurrentValue(double);

  private:
    QHBoxLayout* mainLayout;
    QHBoxLayout* labelLayout;
    QVBoxLayout* sliderSideLayout;
    QVBoxLayout* spinnerSideLayout;
    
    QSpacerItem* verticalSpacer;
    
    QSlider* slider;
    QDoubleSpinBox* spinner;
    
    QLabel* minValueLabel;
    QLabel* maxValueLabel;

    void buildWidget();
    void makeConnections();

  private Q_SLOTS:
    void signalGuiFromSlider(int);
    void signalGuiFromSpinner(double);
    void signalGuiFromSliderReleased();
};

} // end namespace Seg3D

#endif // SLIDERSPINCOMBODOUBLE_H
