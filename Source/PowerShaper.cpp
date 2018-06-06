/*
  ==============================================================================

    PowerShaper.cpp
    Created: 6 Jun 2018 9:06:56pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#include "PowerShaper.h"
#include "HUD_PowerShaper.h"
#include <math.h>

using namespace CuttleFish;

PowerShaper::PowerShaper(int elementId)
	: Effect(elementId)
{
}

PowerShaper::~PowerShaper()
{
}

juce::String PowerShaper::getName() {
	return juce::String("Power Shaper");
}

double PowerShaper::getSignal() {
	double power = ((HUD_PowerShaper*)hudelement)->getPower();

	// Check if supplier exists
	if (!hasSupplier()) { return 0; }
	// Continue if it does

	double wave = supplier->getSignal();

	if (wave > 0) {
		return pow(wave, power);
	} else {
		return -pow(-wave, power);
	}
}