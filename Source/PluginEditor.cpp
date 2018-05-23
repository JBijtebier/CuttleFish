/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CuttleFishAudioProcessorEditor::CuttleFishAudioProcessorEditor (CuttleFishAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

	// Set plugin size
    setSize (800, 450);

	// Master Volume Slider
	addMasterVolumeSlider();
	masterVolumeAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.valueTreeState, "masterVolume", masterVolumeSlider);
}

CuttleFishAudioProcessorEditor::~CuttleFishAudioProcessorEditor()
{
}

//==============================================================================
void CuttleFishAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colour(0.0f, 0.0f, 0.9f, 1.0f));

    // g.setColour (Colours::black);
    // g.setFont (15.0f);
    // g.drawFittedText ("Master Volume", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void CuttleFishAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	masterVolumeSlider.setBounds(40, 30, 20, getHeight() - 60);
}

void CuttleFishAudioProcessorEditor::addMasterVolumeSlider()
{
	// Basic slider parameters and style
	masterVolumeSlider.setSliderStyle(Slider::LinearVertical);
	masterVolumeSlider.setRange(0.0, 1.0, 1);
	masterVolumeSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	masterVolumeSlider.setPopupDisplayEnabled(true, true, this);
	masterVolumeSlider.setTextValueSuffix(" Volume");
	masterVolumeSlider.setValue(0.8);

	// Actually add it
	addAndMakeVisible(&masterVolumeSlider);
}

void CuttleFishAudioProcessorEditor::addCuttleElement(string elementName)
{
	processor.addCuttleElement(elementName);
}

void CuttleFishAudioProcessorEditor::linkElements(int idFrom, int idTo)
{
	processor.linkElements(idFrom, idTo);
}
