/*
  ==============================================================================

    CuttleElement.cpp
    Created: 17 Apr 2018 10:44:45pm
    Author:  Phalcon

  ==============================================================================
*/

#include "CuttleElement.h"

using namespace CuttleFish;

CuttleElement::CuttleElement(int elementId)
{
	id = elementId;
}

  void CuttleElement::setPosition(float x, float y) {
	position.x = x;
	position.y = y;
}

void CuttleElement::setPosition(Point<float> pos) {
	position = pos;
}