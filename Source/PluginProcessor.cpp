/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "HUD_Oscillator.h"
#include "HUD_NoiseGenerator.h"
#include "HUD_LowPassFilter.h"
#include "HUD_HighPassFilter.h"
#include "HUD_Noisifier.h"
#include "HUD_PowerShaper.h"

//==============================================================================
CuttleFishAudioProcessor::CuttleFishAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
		#if ! JucePlugin_IsMidiEffect
		#if ! JucePlugin_IsSynth
				.withInput("Input", AudioChannelSet::stereo(), true)
		#endif
				.withOutput("Output", AudioChannelSet::stereo(), true)
		#endif
			),
	valueTreeState(*this, nullptr)
#endif
{
	//===============
	// Parameters & Value Tree State
	// (PROCESSOR SIDE)
	//===============

	//==============
	// MASTER VOLUME
	//==============
	// Create normalisable range
	NormalisableRange<float> masterVolumeNRange(0.0, 1.0);
	// Add parameter
	valueTreeState.createAndAddParameter("masterVolume", "Master Volume", "Master Volume", masterVolumeNRange, 0.8f, nullptr, nullptr);

	//===============
	// Synth & Voices
	//===============

	cuttleSynth.clearVoices();

	const int voices = 32;

	for (int i = 0; i < voices; i++) {
		SynthVoice* voice = new SynthVoice();
		voice->init();
		cuttleSynth.addVoice(voice);
	}

	cuttleSynth.clearSounds();
	cuttleSynth.addSound(new SynthSound());

	// Start at 1 because output is 0
	currentElementId = 1;
}

CuttleFishAudioProcessor::~CuttleFishAudioProcessor()
{
}

//==============================================================================
const String CuttleFishAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CuttleFishAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CuttleFishAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CuttleFishAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CuttleFishAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CuttleFishAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CuttleFishAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CuttleFishAudioProcessor::setCurrentProgram (int index)
{
}

const String CuttleFishAudioProcessor::getProgramName (int index)
{
    return {};
}

void CuttleFishAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void CuttleFishAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	ignoreUnused(samplesPerBlock);

	// Copy the sampleRate to be sure that it doesn't change during our function (on a different thread?)
	lastSampleRate = sampleRate;

	// Set the sample rate
	cuttleSynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void CuttleFishAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CuttleFishAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void CuttleFishAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	/*

	// =======================
	// MIDI STUFF
	// =======================

	// THIS IS JUST AN EXAMPLE OF SOMETHING I COULD DO LATER IF I HAVE THE TIME.
	// PROBABLY NOT VERY USEFUL TO DIRECTLY CONTROL MIDI INPUT THOUGH.
	// ANY SANE PERSON WOULD WANT TO DO THIS ON THE AUDIO SIGNAL ANYWAY.

	MidiBuffer processedMidi;
	int time;
	MidiMessage m;

	//	Iterate over all midi messages in the buffer and put each (message, time) in (m, time)
	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);) {

		// If it's a note on message, set its velocity to the value we got from the slider
		if (m.isNoteOn()) {
			uint8 newVelocity = (uint8)noteOnVel;
			m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber(), newVelocity);
		}

		// Other possible message types -> ignore them
		else if (m.isNoteOff()) {}
		else if (m.isAftertouch()) {}
		else if (m.isPitchWheel()) {}

		// Add the midi message to our own buffer at the correct timeslot
		processedMidi.addEvent(m, time);
	}

	// Swap the original midi buffer with ours
	// DONT directly edit the original midi buffer because apparently that gives issues
	midiMessages.swapWith(processedMidi);

	*/

	// =======================
	// PARAMETER STUFF
	// =======================

	for (int i = 0; i < cuttleSynth.getNumVoices(); i++) {

		// Single = on purpose! Just a check to see if we can actually assign the voice to the correct type
		if (cuttleVoice = dynamic_cast<SynthVoice*>(cuttleSynth.getVoice(i))) {
			cuttleVoice->setParameter("masterVolume", valueTreeState.getRawParameterValue("masterVolume"));
		}
	}

	// =======================
	// AUDIO STUFF
	// =======================

	buffer.clear();

	cuttleSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool CuttleFishAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* CuttleFishAudioProcessor::createEditor()
{
    return new CuttleFishAudioProcessorEditor (*this);
}

//==============================================================================
void CuttleFishAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CuttleFishAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CuttleFishAudioProcessor();
}

CuttleFish::CuttleElement * CuttleFishAudioProcessor::createCuttleElement(string elementName, int id)
{
	if (elementName == "Output") {
		return new CuttleFish::Output(id);
	}

	if (elementName == "Oscillator") {
		return new CuttleFish::Oscillator(id);
	}

	if (elementName == "Noise Generator") {
		return new CuttleFish::NoiseGenerator(id);
	}

	if (elementName == "Low Pass Filter") {
		return new CuttleFish::LowPassFilter(id);
	}

	if (elementName == "High Pass Filter") {
		return new CuttleFish::HighPassFilter(id);
	}

	if (elementName == "Noisifier") {
		return new CuttleFish::Noisifier(id);
	}

	if (elementName == "Power Shaper") {
		return new CuttleFish::PowerShaper(id);
	}

	Logger::outputDebugString("Could not create cuttle element because name was not found: " + juce::String(elementName));
	return nullptr;
}

CuttleFish::HUDElement * CuttleFishAudioProcessor::createHUDElement(string elementName, AudioProcessorEditor *editor)
{
	Point<int> pos = Point<int>(65, 50);

	if (elementName == "Oscillator") {
		CuttleFish::HUD_Oscillator* elem = new CuttleFish::HUD_Oscillator();
		elem->setEditor(dynamic_cast<CuttleFishAudioProcessorEditor*>(editor));
		elem->setPosition(pos);
		return elem;
	}

	if (elementName == "Noise Generator") {
		CuttleFish::HUD_NoiseGenerator* elem = new CuttleFish::HUD_NoiseGenerator();
		elem->setEditor(dynamic_cast<CuttleFishAudioProcessorEditor*>(editor));
		elem->setPosition(pos);
		return elem;
	}

	if (elementName == "Low Pass Filter") {
		CuttleFish::HUD_LowPassFilter* elem = new CuttleFish::HUD_LowPassFilter();
		elem->setEditor(dynamic_cast<CuttleFishAudioProcessorEditor*>(editor));
		elem->setPosition(pos);
		return elem;
	}

	if (elementName == "High Pass Filter") {
		CuttleFish::HUD_HighPassFilter* elem = new CuttleFish::HUD_HighPassFilter();
		elem->setEditor(dynamic_cast<CuttleFishAudioProcessorEditor*>(editor));
		elem->setPosition(pos);
		return elem;
	}

	if (elementName == "Noisifier") {
		CuttleFish::HUD_Noisifier* elem = new CuttleFish::HUD_Noisifier();
		elem->setEditor(dynamic_cast<CuttleFishAudioProcessorEditor*>(editor));
		elem->setPosition(pos);
		return elem;
	}

	if (elementName == "Power Shaper") {
		CuttleFish::HUD_PowerShaper* elem = new CuttleFish::HUD_PowerShaper();
		elem->setEditor(dynamic_cast<CuttleFishAudioProcessorEditor*>(editor));
		elem->setPosition(pos);
		return elem;
	}

	Logger::outputDebugString("Could not create HUD element because name was not found: " + juce::String(elementName));
	return nullptr;
}

void CuttleFishAudioProcessor::addCuttleElement(string elementName, AudioProcessorEditor *editor)
{
	// Create the HUD element
	CuttleFish::HUDElement *hud = createHUDElement(elementName, editor);
	hudElements.push_back(hud);

	for (int i = 0; i < cuttleSynth.getNumVoices(); i++) {

		// Single = on purpose! Just a check to see if we can actually assign the voice to the correct type
		if (cuttleVoice = dynamic_cast<SynthVoice*>(cuttleSynth.getVoice(i))) {
			// Create the element
			CuttleFish::CuttleElement *element = createCuttleElement(elementName, currentElementId);

			// Add the element to the voice
			cuttleVoice->addCuttleElement(element);

			// Link CuttleElement and HUDElement
			element->setHUDElement(hud);
			hud->addCuttleElement(element);
		}
	}

	hud->instantiateUI();
	hud->makeVisibleInEditor();

	currentElementId++;
}

void CuttleFishAudioProcessor::removeCuttleElement(int id, AudioProcessorEditor * editor)
{
	// --------------------
	// Remove Cuttle elements from HUD elements
	// --------------------
	int i = 0;

	for (std::vector<CuttleFish::HUDElement*>::iterator it = hudElements.begin(); it != hudElements.end(); it++) {
		if ((*it)->getId() == id) {
			(*it)->clearCuttleElements();
			break;
		}

		i++;
	}

	// --------------------
	// Remove Cuttle element
	// --------------------
	for (int i = 0; i < cuttleSynth.getNumVoices(); i++) {

		// Single = on purpose! Just a check to see if we can actually assign the voice to the correct type
		if (cuttleVoice = dynamic_cast<SynthVoice*>(cuttleSynth.getVoice(i))) {
			// Add the element to the voice
			cuttleVoice->removeCuttleElement(id);
		}
	}

	// --------------------
	// Remove HUD element
	// --------------------
	hudElements[i]->removeFromEditor();
	delete hudElements[i];
	hudElements.erase(hudElements.begin() + i, hudElements.begin() + i + 1);

}

void CuttleFishAudioProcessor::linkElements(int idFrom, int idTo)
{
	for (int i = 0; i < cuttleSynth.getNumVoices(); i++) {

		// Single = on purpose! Just a check to see if we can actually assign the voice to the correct type
		if (cuttleVoice = dynamic_cast<SynthVoice*>(cuttleSynth.getVoice(i))) {
			cuttleVoice->linkElements(idFrom, idTo);
		}
	}
}

void CuttleFishAudioProcessor::setNewEditor(AudioProcessorEditor * editor)
{
	CuttleFishAudioProcessorEditor* e = dynamic_cast<CuttleFishAudioProcessorEditor*>(editor);

	for (std::vector<CuttleFish::HUDElement*>::iterator it = hudElements.begin(); it != hudElements.end(); it++) {
		(*it)->setEditor(e);
		(*it)->makeVisibleInEditor();
	}
}
