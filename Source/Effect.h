/*
  ==============================================================================

    Effect.h
    Created: 21 May 2018 9:56:12pm
    Author:  Phalcon

  ==============================================================================
*/

#pragma once
#include "CuttleElement.h"

class Effect : public CuttleElement {
public:
	void setSupplier(CuttleElement *newSupplier);

protected:
	CuttleElement *supplier;
};