/*
  ==============================================================================

    SynthVoice.cpp
    Created: 27 Mar 2018 8:42:09pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#include "SynthVoice.h"
#include <string>

SynthVoice::~SynthVoice()
{
	delete output;

	for (int i = 0; i < generators.size(); i++) {
		delete generators[i];
	}

	for (int i = 0; i < effects.size(); i++) {
		delete effects[i];
	}
}

bool SynthVoice::canPlaySound(SynthesiserSound * sound)
{
	// If we can cast the sound to our synthsound, we can play it.
	return dynamic_cast<SynthSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound * sound, int currentPitchWheelPosition)
{
	// Set cleared to false so know we have to clear the note after its release
	cleared = false;

	// Set the trigger to 1 so we know it's triggered
	env1.trigger = 1;

	// Set frequency of note
	frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);

	// Set velocity (level)
	level = velocity;
	
	for (int i = 0; i < generators.size(); i++) {
		generators[i]->startNote(level, frequency);
	}
}

void SynthVoice::stopNote(float velocity, bool allowTailoff)
{
	// Let the trigger know that we released the note
	env1.trigger = 0;

	for (int i = 0; i < generators.size(); i++) {
		generators[i]->releaseNote();
	}

	// Reset the state of the voice (for reuse on a different keypress)
	// Of course, only if we are not tailing off.
	if (!allowTailoff) { clearCurrentNote(); cleared = true; }
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void SynthVoice::renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
	// Clear the current note if the velocity is 0. (see stopNote)
	if (level == 0) { clearCurrentNote(); }

	// Envelope parameters
	env1.setAttack(20);
	env1.setDecay(500);
	env1.setSustain(0.8);
	env1.setRelease(2000);

	// Iterate over samples
	for (int sample = 0; sample < numSamples; sample++) {

		// Create the (sine) wave
		double wave = output->getSignal();

		// Logger::outputDebugString(juce::String(wave));

		// Create a sound based on the wave and our envelope.
		// double sound = env1.adsr(wave, env1.trigger);

		// If our envelope amplitude is close enough to 0 (inaudible) and  we're in the release phase, our release has finished.
		// That means we can clear the note.
		if ((env1.amplitude <= 0.0001) && (env1.releasephase == 1) && !cleared) {
			clearCurrentNote();
			cleared = true;
		}

		// Iterate over channels and drop our sound sample in the output buffer
		for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++) {
			outputBuffer.addSample(channel, startSample, wave * masterVolume);
		}

		startSample++;
	}
}

void SynthVoice::setParameter(juce::String name, float *value)
{
	if (name == "masterVolume") {
		masterVolume = (double)(*value);
	}
}

void SynthVoice::init()
{
	/*
	output = new Output();

	osc = new Oscillator();
	generators.push_back(osc);

	filter = new LowPassFilter();
	filter->setSupplier(osc);
	output->setSupplier(filter);
	*/
}

void SynthVoice::addCuttleElement(CuttleFish::CuttleElement *element)
{
	// Element is a generator
	if (CuttleFish::Generator *generator = dynamic_cast<CuttleFish::Generator*>(element)) {
		addGenerator(generator);
		return;
	}

	// Element is an effect
	if (CuttleFish::Effect *effect = dynamic_cast<CuttleFish::Effect*>(element)) {
		addEffect(effect);
		return;
	}

	// Element is an output
	if (CuttleFish::Output *output = dynamic_cast<CuttleFish::Output*>(element)) {
		setOutput(output);
		return;
	}
}

void SynthVoice::linkElements(int idFrom, int idTo)
{
	CuttleFish::CuttleElement *from = getCuttleElement(idFrom);
	CuttleFish::CuttleElement *to = getCuttleElement(idTo);

	// 'To' is a generator
	if (CuttleFish::Generator *generator = dynamic_cast<CuttleFish::Generator*>(to)) {
		Logger::outputDebugString("Can't link TO a generator. Can only link FROM an output/generator/effect TO an output/effect.");
		return;
	}

	// 'To' is an effect
	if (CuttleFish::Effect *effect = dynamic_cast<CuttleFish::Effect*>(to)) {
		effect->setSupplier(from);
		return;
	}

	// 'To' is an output
	if (CuttleFish::Output *output = dynamic_cast<CuttleFish::Output*>(to)) {
		output->setSupplier(from);
		return;
	}
}

void SynthVoice::addGenerator(CuttleFish::Generator *generator)
{
	generators.push_back(generator);
}

void SynthVoice::addEffect(CuttleFish::Effect *effect)
{
	effects.push_back(effect);
}

void SynthVoice::setOutput(CuttleFish::Output *outputElement)
{
	output = outputElement;
}

CuttleFish::CuttleElement * SynthVoice::getCuttleElement(int id)
{
	for (int i = 0; i < generators.size(); i++) {
		if (generators[i]->id == id) {
			return generators[i];
		}
	}

	for (int i = 0; i < effects.size(); i++) {
		if (effects[i]->id == id) {
			return effects[i];
		}
	}

	Logger::outputDebugString("getCuttleElement was not found for id: " + id);
	return nullptr;
}
