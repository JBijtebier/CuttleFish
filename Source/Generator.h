/*
  ==============================================================================

    Generator.h
    Created: 18 Apr 2018 12:57:56pm
    Author:  Phalcon

  ==============================================================================
*/

#pragma once
#include "CuttleElement.h"

class Generator : public CuttleElement {
  public:
  
    virtual void startNote(double noteLevel, double noteFrequency) = 0;
	virtual void releaseNote() = 0;
};