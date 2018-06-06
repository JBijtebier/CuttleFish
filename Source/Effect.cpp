/*
  ==============================================================================

    Effect.cpp
    Created: 21 May 2018 9:56:12pm
    Author:  Phalcon

  ==============================================================================
*/

#include "Effect.h"
#include "HUDElement.h"
#include "Output.h"

using namespace CuttleFish;

Effect::Effect(int elementId)
: CuttleElement(elementId)
{
	supplier = nullptr;
	successor = nullptr;
}

void Effect::setSupplier(CuttleElement *newSupplier) {
	supplier = newSupplier;
}

CuttleElement * CuttleFish::Effect::getSupplier()
{
	return supplier;
}

void CuttleFish::Effect::setSuccessor(CuttleElement * newSuccessor)
{
	successor = newSuccessor;
}

CuttleElement * CuttleFish::Effect::getSuccessor()
{
	return successor;
}

bool Effect::hasSupplier()
{
	return (supplier != nullptr);
}

bool Effect::hasSuccessor()
{
	return (successor != nullptr);
}

Line<float> CuttleFish::Effect::getOutgoingLine()
{
	// If successor is output, return the outputposition.
	if (CuttleFish::Output *o = dynamic_cast<CuttleFish::Output*>(successor)) {
		return Line<float>(hudelement->getOutputPosition(), Output::position.toFloat());
	}

	return Line<float>(hudelement->getOutputPosition(), successor->hudelement->getInputPosition());
}

bool CuttleFish::Effect::hasOutgoingLine()
{
	return hasSuccessor();
}
