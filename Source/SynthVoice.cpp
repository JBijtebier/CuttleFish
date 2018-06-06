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

	// Iterate over samples
	for (int sample = 0; sample < numSamples; sample++) {

		// Create the (sine) wave
		double wave = output->getSignal();

		// Logger::outputDebugString("Output: " + juce::String(wave));

		// Create a sound based on the wave and our envelope.
		// double sound = env1.adsr(wave, env1.trigger);

		// If our envelope amplitude is close enough to 0 (inaudible) and  we're in the release phase, our release has finished.
		// That means we can clear the note.
		if (generatorsClear() && !cleared) {
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
	output = new CuttleFish::Output(0);

	/*
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
	if (CuttleFish::Output *newOutput = dynamic_cast<CuttleFish::Output*>(element)) {
		setOutput(newOutput);
		return;
	}
}

void SynthVoice::removeCuttleElement(int id)
{
	Logger::outputDebugString("A1");

	// ----------
	// Remove Links
	// ----------
	CuttleFish::CuttleElement *elem = getCuttleElement(id);

	// Element is a generator
	if (CuttleFish::Generator *generator = dynamic_cast<CuttleFish::Generator*>(elem)) {
		// Successor is output
		if (CuttleFish::Output *o = dynamic_cast<CuttleFish::Output*>(generator->getSuccessor())) {
			o->setSupplier(nullptr);
		}

		// Successor is effect
		if (CuttleFish::Effect *e = dynamic_cast<CuttleFish::Effect*>(generator->getSuccessor())) {
			e->setSupplier(nullptr);
		}
	}

	Logger::outputDebugString("A2");

	// Element is an effect
	if (CuttleFish::Effect *effect = dynamic_cast<CuttleFish::Effect*>(elem)) {
		// Successor is output
		if (CuttleFish::Output *o = dynamic_cast<CuttleFish::Output*>(effect->getSuccessor())) {
			o->setSupplier(nullptr);
		}

		// Successor is effect
		if (CuttleFish::Effect *e = dynamic_cast<CuttleFish::Effect*>(effect->getSuccessor())) {
			e->setSupplier(nullptr);
		}

		// Supplier is generator
		if (CuttleFish::Generator *g = dynamic_cast<CuttleFish::Generator*>(effect->getSupplier())) {
			g->setSuccessor(nullptr);
		}

		// Supplier is effect
		if (CuttleFish::Effect *e = dynamic_cast<CuttleFish::Effect*>(effect->getSupplier())) {
			e->setSuccessor(nullptr);
		}
	}

	Logger::outputDebugString("A3");


	// ----------
	// Delete and remove from vectors
	// ----------
	for (auto it = effects.begin(); it != effects.end();) {
		if ((*it)->id == id) {
			delete * it;
			it = effects.erase(it);
		} else {
			++it;
		}
	}

	for (auto it = generators.begin(); it != generators.end();) {
		if ((*it)->id == id) {
			delete * it;
			it = generators.erase(it);
		}
		else {
			++it;
		}
	}

	Logger::outputDebugString("A4");
}

void SynthVoice::linkElements(int idFrom, int idTo)
{
	CuttleFish::CuttleElement *from = getCuttleElement(idFrom);
	CuttleFish::CuttleElement *to = getCuttleElement(idTo);

	// --------------------
	// Remove FROM's Successor's supplier
	// --------------------
	// OLD LINK: GEN -> ...
	if (CuttleFish::Generator *oldG = dynamic_cast<CuttleFish::Generator*>(from)) {
		// OLD LINK: GEN -> EFFECT
		if (CuttleFish::Effect *e = dynamic_cast<CuttleFish::Effect*>(oldG->getSuccessor())) {
			e->setSupplier(nullptr);
		}
		// OLD LINK: GEN -> OUTPUT
		if (CuttleFish::Output *o = dynamic_cast<CuttleFish::Output*>(oldG->getSuccessor())) {
			o->setSupplier(nullptr);
		}
	}

	// OLD LINK: EFFECT -> ...
	if (CuttleFish::Effect *oldE = dynamic_cast<CuttleFish::Effect*>(from)) {
		// OLD LINK: EFFECT -> EFFECT
		if (CuttleFish::Effect *e = dynamic_cast<CuttleFish::Effect*>(oldE->getSuccessor())) {
			e->setSupplier(nullptr);
		}
		// OLD LINK: EFFECT -> OUTPUT
		if (CuttleFish::Output *o = dynamic_cast<CuttleFish::Output*>(oldE->getSuccessor())) {
			o->setSupplier(nullptr);
		}
	}

	// --------------------
	// Remove TO's Supplier's successor
	// --------------------
	// OLD LINK: OUTPUT <- ...
	if (CuttleFish::Output *oldToO = dynamic_cast<CuttleFish::Output*>(to)) {
		// OLD LINK: OUTPUT <- EFFECT
		if (CuttleFish::Effect *e = dynamic_cast<CuttleFish::Effect*>(oldToO->getSupplier())) {
			e->setSuccessor(nullptr);
		}
		// OLD LINK: OUTPUT <- GENERATOR
		if (CuttleFish::Generator *g = dynamic_cast<CuttleFish::Generator*>(oldToO->getSupplier())) {
			g->setSuccessor(nullptr);
		}
	}

	// OLD LINK: EFFECT <- ...
	if (CuttleFish::Effect *oldToE = dynamic_cast<CuttleFish::Effect*>(to)) {
		// OLD LINK: EFFECT <- EFFECT
		if (CuttleFish::Effect *e = dynamic_cast<CuttleFish::Effect*>(oldToE->getSupplier())) {
			e->setSuccessor(nullptr);
		}
		// OLD LINK: EFFECT <- GENERATOR
		if (CuttleFish::Generator *g = dynamic_cast<CuttleFish::Generator*>(oldToE->getSupplier())) {
			g->setSuccessor(nullptr);
		}
	}

	// --------------------
	// SET THE NEW LINKS
	// --------------------

	// To a generator
	if (CuttleFish::Generator *generator = dynamic_cast<CuttleFish::Generator*>(to)) {
		Logger::outputDebugString("Can't link TO a generator. Can only link FROM an output/generator/effect TO an output/effect.");
		return;
	}

	// To an effect
	if (CuttleFish::Effect *toEffect = dynamic_cast<CuttleFish::Effect*>(to)) {

		toEffect->setSupplier(from);
	}

	// To an output
	if (CuttleFish::Output *toOutput = dynamic_cast<CuttleFish::Output*>(to)) {
		toOutput->setSupplier(from);
	}

	// From a generator
	if (CuttleFish::Generator *fromGenerator = dynamic_cast<CuttleFish::Generator*>(from)) {
		fromGenerator->setSuccessor(to);
	}

	// From an effect
	if (CuttleFish::Effect *fromEffect = dynamic_cast<CuttleFish::Effect*>(from)) {
		fromEffect->setSuccessor(to);
	}

	// From an output
	if (CuttleFish::Output *o = dynamic_cast<CuttleFish::Output*>(from)) {
		Logger::outputDebugString("Can't link FROM an output. Can only link FROM a generator/effect TO an output/effect.");
		return;
	}

	clearCurrentNote();
	cleared = true;
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
	if (id == 0) {
		return output;
	}

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

	Logger::outputDebugString("getCuttleElement was not found for id: " + juce::String(id));
	return nullptr;
}

bool SynthVoice::generatorsClear() {
	for (int i = 0; i < generators.size(); i++) {
		if (!generators[i]->isClear()) {
			return false;
		}
	}

	return true;
}