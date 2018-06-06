/*
  ==============================================================================

    NoiseGenerator.cpp
    Created: 6 Jun 2018 7:55:06pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#include "NoiseGenerator.h"
#include "HUD_NoiseGenerator.h"

using namespace CuttleFish;

NoiseGenerator::NoiseGenerator(int elementId)
	: Generator(elementId)
{
	frequency = 0;
	level = 0;
	env = maxiEnv();
	rnd = Random();
}

NoiseGenerator::~NoiseGenerator()
{
}

void NoiseGenerator::startNote(double noteLevel, double noteFrequency) {
	level = noteLevel;
	frequency = noteFrequency;
	env.trigger = 1;
}

void NoiseGenerator::releaseNote() {
	env.trigger = 0;
}

bool CuttleFish::NoiseGenerator::isClear()
{
	if (env.trigger == 1) {
		return false;
	}
	else {
		return (env.amplitude <= 0.0001) && (env.releasephase == 1);
	}
}

juce::String NoiseGenerator::getName() {
	return juce::String("Noise Generator");
}

double NoiseGenerator::getSignal() {
	env.setAttack(((HUD_NoiseGenerator*)hudelement)->getEnvA());
	env.setDecay(((HUD_NoiseGenerator*)hudelement)->getEnvD());
	env.setSustain(((HUD_NoiseGenerator*)hudelement)->getEnvS());
	env.setRelease(((HUD_NoiseGenerator*)hudelement)->getEnvR());

	double wave = getWave() * level;

	return env.adsr(wave, env.trigger);
}

double NoiseGenerator::getWave() {
	return rnd.nextDouble() * 2 - 1;
}