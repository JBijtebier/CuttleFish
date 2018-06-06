/*
  ==============================================================================

    Oscillator.cpp
    Created: 19 Apr 2018 12:08:17am
    Author:  Phalcon

  ==============================================================================
*/

#include "Oscillator.h"
#include "HUD_Oscillator.h"

using namespace CuttleFish;

Oscillator::Oscillator(int elementId)
: Generator(elementId)
{
	frequency = 0;
	level = 0;
	waveTable = 2;
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

bool CuttleFish::Oscillator::isClear()
{
	if (env.trigger == 1) {
		return false;
	}
	else {
		return (env.amplitude <= 0.0001) && (env.releasephase == 1);
	}
}

juce::String Oscillator::getName() {
	return juce::String("Oscillator");
}

double Oscillator::getSignal() {
	env.setAttack(((HUD_Oscillator*)hudelement)->getEnvA());
	env.setDecay(((HUD_Oscillator*)hudelement)->getEnvD());
	env.setSustain(((HUD_Oscillator*)hudelement)->getEnvS());
	env.setRelease(((HUD_Oscillator*)hudelement)->getEnvR());

	double wave = getWave() * level;

	return env.adsr(wave, env.trigger);
}

double Oscillator::getWave() {
	waveTable = ((HUD_Oscillator*)hudelement)->getWaveTable();

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