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

		void addCuttleElement(CuttleFish::CuttleElement *element);

		void linkElements(int idFrom, int idTo);

	private:

		/*
			Cuttle Elements
		*/

		std::vector<CuttleFish::Generator *> generators;
		std::vector<CuttleFish::Effect *> effects;
		CuttleFish::Output* output;

		/*
			Other Stuff
		*/

		double level;
		double masterVolume;
		double frequency;

		bool cleared;

		/*
			To be removed
		*/

		bool generatorsClear();

		//==============================================================================
		// CUTTLE ELEMENT - VOICES
		//==============================================================================
		void addGenerator(CuttleFish::Generator *generator);

		void addEffect(CuttleFish::Effect *effect);

		void setOutput(CuttleFish::Output *outputElement);

		CuttleFish::CuttleElement* getCuttleElement(int id);
};