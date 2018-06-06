/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "SynthVoice.h"
#include <vector>

//==============================================================================
/**
*/
class CuttleFishAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    CuttleFishAudioProcessor();
    ~CuttleFishAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	//==============================================================================
	AudioProcessorValueTreeState valueTreeState;

	//==============================================================================
	// CUTTLE ELEMENT - VOICES
	//==============================================================================
	CuttleFish::CuttleElement* createCuttleElement(string elementName, int id);
	CuttleFish::HUDElement* createHUDElement(string elementName, AudioProcessorEditor *editor);
	void addCuttleElement(string elementName, AudioProcessorEditor *editor);
	void removeCuttleElement(int id, AudioProcessorEditor *editor);
	void linkElements(int idFrom, int idTo);

	//==============================================================================
	std::vector<CuttleFish::HUDElement*> hudElements;
	void setNewEditor(AudioProcessorEditor *editor);

private:
	Synthesiser cuttleSynth;
	SynthVoice* cuttleVoice;

	double lastSampleRate;

	//==============================================================================
	// CUTTLE ELEMENT - VOICES
	//==============================================================================
	int currentElementId;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CuttleFishAudioProcessor)
};
