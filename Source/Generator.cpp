/*
  ==============================================================================

    Generator.cpp
    Created: 18 Apr 2018 12:57:56pm
    Author:  Phalcon

  ==============================================================================
*/

#include "Generator.h"
#include "HUDElement.h"
#include "Output.h"

using namespace CuttleFish;

Generator::Generator(int elementId)
: CuttleElement(elementId)
{
	successor = nullptr;
}

void CuttleFish::Generator::setSuccessor(CuttleElement * newSuccessor)
{
	successor = newSuccessor;
}

CuttleElement * CuttleFish::Generator::getSuccessor()
{
	return successor;
}

bool Generator::hasSuccessor()
{
	return (successor != nullptr);
}

Line<float> CuttleFish::Generator::getOutgoingLine()
{
	// If successor is output, return the outputposition.
	if (CuttleFish::Output *o = dynamic_cast<CuttleFish::Output*>(successor)) {
		return Line<float>(hudelement->getOutputPosition(), Output::position.toFloat());
	}

	return Line<float>(hudelement->getOutputPosition(), successor->hudelement->getInputPosition());
}

bool CuttleFish::Generator::hasOutgoingLine()
{
	Logger::outputDebugString("Asking if line exists...");
	Logger::outputDebugString(juce::String((int)hasSuccessor()));
	return hasSuccessor();
}
