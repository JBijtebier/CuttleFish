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
	supplier = nullptr;
}

Output::~Output()
{
}

juce::String Output::getName() {
    return juce::String("Output");
}

double Output::getSignal() {
	// Check if supplier exists
	if (!hasSupplier()) { return 0; }
	// Continue if it does

    return supplier->getSignal();
}
    
void Output::setSupplier(CuttleElement *newSupplier) {
    supplier = newSupplier;
}

bool Output::hasSupplier()
{
	return (supplier != nullptr);
}
