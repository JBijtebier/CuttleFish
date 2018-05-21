/*
  ==============================================================================

    LowPassFilter.cpp
    Created: 21 May 2018 9:58:00pm
    Author:  Phalcon

  ==============================================================================
*/

#include "LowPassFilter.h"

LowPassFilter::LowPassFilter() {
	filter = maxiFilter();
	cutoff = 1;
}

LowPassFilter::~LowPassFilter()
{
}

juce::String LowPassFilter::getName() {
	return juce::String("Low Pass Filter");
}

double LowPassFilter::getSignal() {
	double wave = supplier->getSignal();
	return filter.lopass(wave, cutoff);
}