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

	// Wave Table Slider
	addWaveTableSlider();
	waveTableAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.valueTreeState, "waveTable", waveTableSlider);

	// Cutoff Slider
	addCutoffSlider();
	cutoffAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.valueTreeState, "cutoff", cutoffSlider);
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
	waveTableSlider.setBounds(80, 30, 200, 200);
	cutoffSlider.setBounds(280, 30, 200, 200);
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

void CuttleFishAudioProcessorEditor::addWaveTableSlider()
{
	// Basic slider parameters and style
	waveTableSlider.setSliderStyle(Slider::Rotary);
	waveTableSlider.setRotaryParameters (MathConstants<float>::pi * 1.2f, MathConstants<float>::pi * 2.8f, false);
	waveTableSlider.setRange(0.0, 3.0, 1);
	waveTableSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	waveTableSlider.setPopupDisplayEnabled(true, true, this);
	waveTableSlider.setTextValueSuffix(" Wave Shape");
	waveTableSlider.setValue(0.0);
	// waveTableSlider.setColour(Slider::backgroundColourId, Colour(0.5f, 1.0f, 1.0f, 1.0f));
	// waveTableSlider.setColour(Slider::rotarySliderFillColourId, Colour(0.5f, 1.0f, 1.0f, 1.0f));
	// waveTableSlider.setColour(Slider::rotarySliderOutlineColourId, Colour(0.0f, 1.0f, 1.0f, 1.0f));

	// Actually add it
	addAndMakeVisible(&waveTableSlider);
}

void CuttleFishAudioProcessorEditor::addCutoffSlider()
{
	// Basic slider parameters and style
	cutoffSlider.setSliderStyle(Slider::Rotary);
	cutoffSlider.setRotaryParameters(MathConstants<float>::pi * 1.2f, MathConstants<float>::pi * 2.8f, false);
	cutoffSlider.setRange(0.0, 1.0, 1);
	cutoffSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	cutoffSlider.setPopupDisplayEnabled(true, true, this);
	cutoffSlider.setTextValueSuffix(" Cutoff");
	cutoffSlider.setValue(0.0);
	// waveTableSlider.setColour(Slider::backgroundColourId, Colour(0.5f, 1.0f, 1.0f, 1.0f));
	// waveTableSlider.setColour(Slider::rotarySliderFillColourId, Colour(0.5f, 1.0f, 1.0f, 1.0f));
	// waveTableSlider.setColour(Slider::rotarySliderOutlineColourId, Colour(0.0f, 1.0f, 1.0f, 1.0f));

	// Actually add it
	addAndMakeVisible(&cutoffSlider);
}

void CuttleFishAudioProcessorEditor::addCuttleElement(string elementName)
{
	processor.addCuttleElement(elementName);
}

void CuttleFishAudioProcessorEditor::linkElements(int idFrom, int idTo)
{
	processor.linkElements(idFrom, idTo);
}
