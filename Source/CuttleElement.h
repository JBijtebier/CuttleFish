/*
  ==============================================================================

    CuttleElement.h
    Created: 17 Apr 2018 10:44:45pm
    Author:  Phalcon

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class CuttleElement {
  public:
    CuttleElement();
    ~CuttleElement();
  
    virtual juce::String getName() = 0;
}