/*
  ==============================================================================

    SynthVoice.h
    Created: 27 Mar 2018 8:42:09pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"
#include "Output.h"
#include "Oscillator.h"
#include "LowPassFilter.h"
#include <vector>

class SynthVoice : public SynthesiserVoice {
	public:
		~SynthVoice();

		bool canPlaySound(SynthesiserSound *sound) override;

		void startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override;

		void stopNote(float velocity, bool allowTailoff) override;

		void pitchWheelMoved(int newPitchWheelValue) override;

		void controllerMoved(int controllerNumber, int newControllerValue) override;

		void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;

		void setParameter(juce::String name, float* value);

		void init();

	private:

		/*
			Cuttle Elements
		*/

		std::vector<Generator *> generators;
		Output* output;

		/*
			Other Stuff
		*/

		double getWave();

		double level;
		double masterVolume;
		double waveTable;
		double frequency;
		double cutoff;

		bool cleared;

		maxiOsc osc1;
		maxiEnv env1;

		/*
			To be removed
		*/

		Oscillator *osc;
		LowPassFilter *filter;
};