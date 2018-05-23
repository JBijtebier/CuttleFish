/*
  ==============================================================================

    Output.cpp
    Created: 18 Apr 2018 1:07:54pm
    Author:  Phalcon

  ==============================================================================
*/

#include "Output.h"

using namespace CuttleFish;

Output::Output(int elementId)
: CuttleElement(elementId)
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

void CuttleFish::Output::instantiateUI()
{
}
    
void Output::setSupplier(CuttleElement *newSupplier) {
    supplier = newSupplier;
}