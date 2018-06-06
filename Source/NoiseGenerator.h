/*
  ==============================================================================

    NoiseGenerator.h
    Created: 6 Jun 2018 7:55:06pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#pragma once
#include "Generator.h"
#include "maximilian.h"

namespace CuttleFish {

	class NoiseGenerator : public Generator {
	public:
		NoiseGenerator(int elementId);
		~NoiseGenerator();

		void startNote(double noteLevel, double noteFrequency) override;

		void releaseNote() override;

		bool isClear() override;

		juce::String getName() override;

		double getSignal() override;

		double getWave();

		double level;
		double frequency;

	private:

		Random rnd;
		maxiEnv env;
	};

}

