/*
  ==============================================================================

    Noisifier.cpp
    Created: 6 Jun 2018 8:35:17pm
    Author:  Phalcon

  ==============================================================================
*/

#include "Noisifier.h"
#include "HUD_Noisifier.h"

using namespace CuttleFish;

Noisifier::Noisifier(int elementId)
	: Effect(elementId)
{
	rnd = Random();
}

Noisifier::~Noisifier()
{
}

juce::String Noisifier::getName() {
	return juce::String("Noisifier");
}

double Noisifier::getSignal() {
	double amount = ((HUD_Noisifier*)hudelement)->getAmount();

	// Check if supplier exists
	if (!hasSupplier()) { return 0; }
	// Continue if it does

	double wave = supplier->getSignal();
	double rand = rnd.nextDouble() * 2 - 1;

	return (1 - amount) * wave + amount * (wave * rand);
}