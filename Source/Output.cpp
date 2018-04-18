/*
  ==============================================================================

    Output.cpp
    Created: 18 Apr 2018 1:07:54pm
    Author:  Phalcon

  ==============================================================================
*/

#include "Output.h"

Output::Output()
{
}

Output::~Output()
{
}

juce::String Output::getName() {
    return juce::String("Output");
}

double Output::getSignal() {
    return supplier->getSignal();
}
    
void Output::setSupplier(CuttleElement *newSupplier) {
    supplier = newSupplier;
}