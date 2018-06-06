/*
  ==============================================================================

    HighPassFilter.cpp
    Created: 6 Jun 2018 4:47:21pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#include "HighPassFilter.h"
#include "HUD_HighPassFilter.h"

using namespace CuttleFish;

HighPassFilter::HighPassFilter(int elementId)
	: Effect(elementId)
{
	filter = maxiFilter();
	cutoff = 0.1;
}

HighPassFilter::~HighPassFilter()
{
}

juce::String HighPassFilter::getName() {
	return juce::String("High Pass Filter");
}

double HighPassFilter::getSignal() {
	cutoff = ((HUD_HighPassFilter*)hudelement)->getCutoff();

	// Check if supplier exists
	if (!hasSupplier()) { return 0; }
	// Continue if it does

	double wave = supplier->getSignal();
	return filter.hipass(wave, cutoff);
}