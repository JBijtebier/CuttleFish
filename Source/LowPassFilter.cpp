/*
  ==============================================================================

    LowPassFilter.cpp
    Created: 21 May 2018 9:58:00pm
    Author:  Phalcon

  ==============================================================================
*/

#include "LowPassFilter.h"
#include "HUD_LowPassFilter.h"

using namespace CuttleFish;

LowPassFilter::LowPassFilter(int elementId)
: Effect(elementId)
{
	filter = maxiFilter();
	cutoff = 0.1;
}

LowPassFilter::~LowPassFilter()
{
}

juce::String LowPassFilter::getName() {
	return juce::String("Low Pass Filter");
}

double LowPassFilter::getSignal() {
	cutoff = ((HUD_LowPassFilter*)hudelement)->getCutoff();

	// Check if supplier exists
	if (!hasSupplier()) { return 0; }
	// Continue if it does

	double wave = supplier->getSignal();
	return filter.lopass(wave, cutoff);
}