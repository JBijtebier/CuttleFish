/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "CuttleElement.h"

//==============================================================================
class CuttleFishAudioProcessorEditor  : public AudioProcessorEditor									
{
public:
    CuttleFishAudioProcessorEditor (CuttleFishAudioProcessor&);
    ~CuttleFishAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CuttleFishAudioProcessor& processor;

	// Slider: Master Volume
	Slider masterVolumeSlider;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> masterVolumeAttachment;
	void addMasterVolumeSlider();

	// Slider: Wavetable
	Slider waveTableSlider;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> waveTableAttachment;
	void addWaveTableSlider();

	// Slider: Cutoff
	Slider cutoffSlider;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> cutoffAttachment;
	void addCutoffSlider();

	//==============================================================================
	// Cuttle Elements
	//==============================================================================
	void addCuttleElement(string elementName);
	void linkElements(int idFrom, int idTo);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CuttleFishAudioProcessorEditor)
};
