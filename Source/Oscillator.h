/*
  ==============================================================================

    Oscillator.h
    Created: 19 Apr 2018 12:08:17am
    Author:  Jens Bijtebier

  ==============================================================================
*/

#pragma once
#include "Generator.h"
#include "maximilian.h"

namespace CuttleFish {

	class Oscillator : public Generator {
	public:
		Oscillator(int elementId);
		~Oscillator();

		void startNote(double noteLevel, double noteFrequency) override;

		void releaseNote() override;

		bool isClear() override;

		juce::String getName() override;

		double getSignal() override;

		double getWave();

		double waveTable;
		double level;
		double frequency;

	private:

		maxiOsc osc;
		maxiEnv env;
	};

}

