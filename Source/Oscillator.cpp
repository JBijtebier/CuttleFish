/*
  ==============================================================================

    Oscillator.cpp
    Created: 19 Apr 2018 12:08:17am
    Author:  Phalcon

  ==============================================================================
*/

#include "Oscillator.h"

using namespace CuttleFish;

Oscillator::Oscillator(int elementId)
: Generator(elementId)
{
	frequency = 0;
	level = 0;
	env = maxiEnv();
	osc = maxiOsc();
}

Oscillator::~Oscillator()
{
}

void Oscillator::startNote(double noteLevel, double noteFrequency) {
	level = noteLevel;
	frequency = noteFrequency;
	env.trigger = 1;
}

void Oscillator::releaseNote() {
	env.trigger = 0;
}

juce::String Oscillator::getName() {
	return juce::String("Oscillator");
}

double Oscillator::getSignal() {
	env.setAttack(20);
	env.setDecay(500);
	env.setSustain(0.8);
	env.setRelease(2000);

	//Logger::outputDebugString(juce::String(frequency));
	double wave = getWave() * level;

	return env.adsr(wave, env.trigger);
	//return getWave() * level;
}

double Oscillator::getWave() {
	// Sine -> Triangle
	if (waveTable < 1.0f) {
		double t = waveTable;
		return ((1 - t) * osc.sinewave(frequency / 2) + t * osc.triangle(frequency / 2)) * level;
	}
	// Triangle -> Saw
	else if (waveTable < 2.0f) {
		double t = waveTable - 1.0f;
		return ((1 - t) * osc.triangle(frequency / 2) + t * osc.saw(frequency / 2)) * level;
	}
	// Saw -> Square
	else {
		double t = waveTable - 2.0f;
		return ((1 - t) * osc.saw(frequency / 2) + t * osc.square(frequency / 2)) * level;
	}
}