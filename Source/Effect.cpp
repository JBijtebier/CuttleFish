/*
  ==============================================================================

    Effect.cpp
    Created: 21 May 2018 9:56:12pm
    Author:  Phalcon

  ==============================================================================
*/

#include "Effect.h"

using namespace CuttleFish;

Effect::Effect(int elementId)
: CuttleElement(elementId)
{
}

  void Effect::setSupplier(CuttleElement *newSupplier) {
	supplier = newSupplier;
}