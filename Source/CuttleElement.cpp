/*
  ==============================================================================

    CuttleElement.cpp
    Created: 17 Apr 2018 10:44:45pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#include "CuttleElement.h"

using namespace CuttleFish;

CuttleElement::CuttleElement(int elementId)
{
	id = elementId;
}

void CuttleFish::CuttleElement::setHUDElement(HUDElement * elem)
{
	hudelement = elem;
}
