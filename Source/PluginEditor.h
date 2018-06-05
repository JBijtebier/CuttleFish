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
class CuttleFishAudioProcessorEditor  : public AudioProcessorEditor, public Button::Listener									
{
public:
    CuttleFishAudioProcessorEditor (CuttleFishAudioProcessor&);
    ~CuttleFishAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void setConnectionInput(int id);
	void setConnectionOutput(int id);

	void log(juce::String s);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CuttleFishAudioProcessor& processor;

	// Slider: Master Volume
	Slider masterVolumeSlider;
	ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> masterVolumeAttachment;
	void addMasterVolumeSlider();

	// New Element
	ComboBox elementBox;
	TextButton newElement;
	void addElementBox();
	void buttonClicked(Button* btn) override;

	// Frames
	Label topFrame;
	Label masterVolumeFrame;
	void addFrames();

	// OutputButton
	Label outputFrame;
	TextButton outputButton;
	void addOutputFrame();

	Label logLabel;

	//==============================================================================
	// Cuttle Elements
	//==============================================================================
	void addCuttleElement(string elementName);
	void linkElements(int idFrom, int idTo);

	int connectionInputId;
	int connectionOutputId;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CuttleFishAudioProcessorEditor)
};
