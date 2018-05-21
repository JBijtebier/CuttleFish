/*
  ==============================================================================

    LowPassFilter.h
    Created: 21 May 2018 9:58:00pm
    Author:  Phalcon

  ==============================================================================
*/

#pragma once

#include "Effect.h"
#include "maximilian.h"

class LowPassFilter : public Effect {
public:
	LowPassFilter();
	~LowPassFilter();

	juce::String getName() override;

	double getSignal() override;

	double cutoff;

private:

	maxiFilter filter;
};