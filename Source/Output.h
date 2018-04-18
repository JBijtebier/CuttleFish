/*
  ==============================================================================

    Output.h
    Created: 18 Apr 2018 1:07:54pm
    Author:  Phalcon

  ==============================================================================
*/

#pragma once
#include "CuttleElement.h"

class Output : public CuttleElement {
  public:
    Output();
    ~Output();

    juce::String getName() override;
    
    double getSignal() override;
    
    void setSupplier(CuttleElement *newSupplier);
    
  private:
    CuttleElement *supplier;
};