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
    setSize (1280, 720);

	// Frames
	addFrames();
	addElementBox();
	addOutputFrame();

	// Master Volume Slider
	addMasterVolumeSlider();
	masterVolumeAttachment = new AudioProcessorValueTreeState::SliderAttachment(processor.valueTreeState, "masterVolume", masterVolumeSlider);

	// çonnection id's
	connectionInputId = -1;
	connectionOutputId = -1;

	// ==========================================================
	// CREATE CUTTLE ELEMENTS BY HAND ATM, DO IT IN UI LATER
	// ==========================================================
	addCuttleElement("Oscillator"); // id 1
	linkElements(1, 0); // LPF -> OUT
}

CuttleFishAudioProcessorEditor::~CuttleFishAudioProcessorEditor()
{
}

//==============================================================================
void CuttleFishAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colour(230, 230, 230));

    // g.setColour (Colours::black);
    // g.setFont (15.0f);
    // g.drawFittedText ("Master Volume", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void CuttleFishAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	masterVolumeSlider.setBounds(20, 80, 20, getHeight() - 100);
	topFrame.setBounds(0, 0, getWidth(), 45);
	masterVolumeFrame.setBounds(0, topFrame.getHeight(), 60, getHeight() - topFrame.getHeight());
	elementBox.setBounds(0, 0, 200, topFrame.getHeight());
	newElement.setBounds(200, 0, topFrame.getHeight(), topFrame.getHeight());
	outputFrame.setBounds(getWidth() - 40, topFrame.getHeight(), 40, getHeight() - topFrame.getHeight());
	outputButton.setBounds(getWidth() - 35, topFrame.getHeight() / 2 + getHeight() / 2 - 15, 30, 30);
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

void CuttleFishAudioProcessorEditor::addElementBox()
{
	// Basic slider parameters and style
	elementBox.setColour(ComboBox::ColourIds::backgroundColourId, Colour(29, 33, 37));
	elementBox.setColour(ComboBox::ColourIds::textColourId, Colour(230, 230, 230));
	elementBox.setColour(ComboBox::ColourIds::buttonColourId, Colour(29, 33, 37));
	elementBox.addSectionHeading("Generators");
	elementBox.addItem("Oscillator", 1);
	elementBox.addSeparator();
	elementBox.addSectionHeading("Effects");
	elementBox.addItem("Low Pass Filter", 2);
	elementBox.setSelectedId(1);
	addAndMakeVisible(&elementBox);

	// Button
	newElement.setColour(TextButton::ColourIds::textColourOffId, Colour(230, 230, 230));
	newElement.setColour(TextButton::ColourIds::buttonColourId, Colour(29, 33, 37));
	newElement.setButtonText("+");
	newElement.setName("NewElement");
	newElement.addListener(this);
	addAndMakeVisible(&newElement);

	// Actually add it
	addAndMakeVisible(&elementBox);
}

void CuttleFishAudioProcessorEditor::buttonClicked(Button * btn)
{
	if (btn->getName() == "NewElement") {
		addCuttleElement(elementBox.getText().toStdString());
	}

	if (btn->getName() == "OutputButton") {
		setConnectionOutput(0);
	}
}

void CuttleFishAudioProcessorEditor::addFrames()
{
	topFrame.setColour(Label::ColourIds::backgroundColourId, Colour(29, 33, 37));
	topFrame.setText("", juce::NotificationType::dontSendNotification);
	addAndMakeVisible(&topFrame);

	masterVolumeFrame.setColour(Label::ColourIds::backgroundColourId, Colour(247, 247, 247));
	masterVolumeFrame.setText("", juce::NotificationType::dontSendNotification);
	addAndMakeVisible(&masterVolumeFrame);
}

void CuttleFishAudioProcessorEditor::addOutputFrame()
{
	// Frame
	outputFrame.setColour(Label::ColourIds::backgroundColourId, Colour(247, 247, 247));
	outputFrame.setText("", juce::NotificationType::dontSendNotification);
	addAndMakeVisible(&outputFrame);

	// Button
	outputButton.setColour(TextButton::ColourIds::textColourOffId, Colour(30, 30, 30));
	outputButton.setColour(TextButton::ColourIds::buttonColourId, Colour(168, 231, 255));
	outputButton.setButtonText("O");
	outputButton.setName("OutputButton");
	outputButton.addListener(this);
	addAndMakeVisible(&outputButton);
}


void CuttleFishAudioProcessorEditor::addCuttleElement(string elementName)
{
	processor.addCuttleElement(elementName, this);
}

void CuttleFishAudioProcessorEditor::linkElements(int idFrom, int idTo)
{
	// Error checking
	if (idFrom == -1) { return; }
	if (idTo == -1) { return; }
	if (idFrom == idTo) { return; }

	// Link
	processor.linkElements(idFrom, idTo);

	// Reset state
	connectionInputId = -1;
	connectionOutputId = -1;
}

void CuttleFishAudioProcessorEditor::setConnectionInput(int id)
{
	connectionInputId = id;
}

void CuttleFishAudioProcessorEditor::setConnectionOutput(int id)
{
	connectionOutputId = id;
	linkElements(connectionInputId, connectionOutputId);
}
