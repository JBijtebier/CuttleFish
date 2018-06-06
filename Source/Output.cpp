/*
  ==============================================================================

    Output.cpp
    Created: 18 Apr 2018 1:07:54pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#include "Output.h"

using namespace CuttleFish;

Point<int> Output::position = Point<int>();

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

CuttleElement * CuttleFish::Output::getSupplier()
{
	return supplier;
}

bool Output::hasSupplier()
{
	return (supplier != nullptr);
}

Line<float> CuttleFish::Output::getOutgoingLine()
{
	Logger::outputDebugString("Can't get outgoing line from an output. This shouldn't be asked for anyway.");

	return Line<float>();
}

bool CuttleFish::Output::hasOutgoingLine()
{
	return false;
}
