/*
  ==============================================================================

    SynthVoice.cpp
    Created: 27 Mar 2018 8:42:09pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#include "SynthVoice.h"
#include <string>

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
}

void SynthVoice::stopNote(float velocity, bool allowTailoff)
{
	// Let the trigger know that we released the note
	env1.trigger = 0;

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
		double wave = getWave();

		// Create a sound based on the wave and our envelope.
		double sound = env1.adsr(wave, env1.trigger);

		// If our envelope amplitude is close enough to 0 (inaudible) and  we're in the release phase, our release has finished.
		// That means we can clear the note.
		if ((env1.amplitude <= 0.0001) && (env1.releasephase == 1) && !cleared) {
			clearCurrentNote();
			cleared = true;
		}

		// Iterate over channels and drop our sound sample in the output buffer
		for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++) {
			outputBuffer.addSample(channel, startSample, sound * masterVolume);
		}

		startSample++;
	}
}

void SynthVoice::setParameter(juce::String name, float *value)
{
	if (name == "masterVolume") {
		masterVolume = (double)(*value);
	}

	else if (name == "waveTable") {
		waveTable = (double)(*value);
	}
}

double SynthVoice::getWave() {

	/* Since we are executing two oscillator functions every time, the phase gets updated twice.
	 * So we only use half the frequency, so that it updates once.
	 */

	// Sine -> Triangle
	if (waveTable < 1.0f) {
		double t = waveTable;
		return ((1 - t) * osc1.sinewave(frequency / 2) + t * osc1.triangle(frequency / 2)) * level;
	}
	// Triangle -> Saw
	else if (waveTable < 2.0f) {
		double t = waveTable - 1.0f;
		return ((1 - t) * osc1.triangle(frequency / 2) + t * osc1.saw(frequency / 2)) * level;
	}
	// Saw -> Square
	else {
		double t = waveTable - 2.0f;
		return ((1 - t) * osc1.saw(frequency / 2) + t * osc1.square(frequency / 2)) * level;
	}
}
