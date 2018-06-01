/*
  ==============================================================================

    HUD_Oscillator.cpp
    Created: 1 Jun 2018 7:12:18pm
    Author:  Phalcon

  ==============================================================================
*/

#include "HUD_Oscillator.h"

using namespace CuttleFish;

HUD_Oscillator::HUD_Oscillator(AudioProcessorEditor *e)
	: HUDElement(e)
{
	setSize(200, 230);
}

void CuttleFish::HUD_Oscillator::instantiateControls()
{
	// -------------
	// WAVE TABLE
	// -------------
	// Params
	waveTableSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	waveTableSlider.setRange(0.0, 3.0, 0.01);
	waveTableSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	waveTableSlider.setPopupDisplayEnabled(true, true, editor);
	waveTableSlider.setTextValueSuffix(" Wave Table");
	waveTableSlider.setValue(0.0);
	// Actually add it
	editor->addAndMakeVisible(&waveTableSlider);
	// Sizing
	waveTableSlider.setBounds(transform.getX() + 40, transform.getY() + 45, 120, 120);
	// Label
	waveTableLabel.setBounds(transform.getX() + 40, transform.getY() + 35, 120, 15);
	waveTableLabel.setColour(Label::ColourIds::textColourId, Colour(38, 50, 56));
	waveTableLabel.setJustificationType(Justification::centred);
	waveTableLabel.setFont(Font(12, Font::bold));
	waveTableLabel.setText("Wave Table", NotificationType::dontSendNotification);
	editor->addAndMakeVisible(&waveTableLabel);

	// -------------
	// Env A
	// -------------
	// Params
	envASlider.setSliderStyle(Slider::RotaryVerticalDrag);
	envASlider.setRange(10, 5000, 1);
	envASlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	envASlider.setPopupDisplayEnabled(true, true, editor);
	envASlider.setTextValueSuffix(" msec Attack");
	envASlider.setValue(25);
	// Actually add it
	editor->addAndMakeVisible(&envASlider);
	// Sizing
	envASlider.setBounds(transform.getX() + 0, transform.getY() + 180, 50, 50);
	// Label
	envALabel.setBounds(transform.getX() + 0, transform.getY() + 170, 50, 15);
	envALabel.setColour(Label::ColourIds::textColourId, Colour(38, 50, 56));
	envALabel.setJustificationType(Justification::centred);
	envALabel.setFont(Font(12, Font::bold));
	envALabel.setText("A", NotificationType::dontSendNotification);
	editor->addAndMakeVisible(&envALabel);

	// -------------
	// Env D
	// -------------
	// Params
	envDSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	envDSlider.setRange(10, 5000, 1);
	envDSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	envDSlider.setPopupDisplayEnabled(true, true, editor);
	envDSlider.setTextValueSuffix(" msec Decay");
	envDSlider.setValue(10);
	// Actually add it
	editor->addAndMakeVisible(&envDSlider);
	// Sizing
	envDSlider.setBounds(transform.getX() + 50, transform.getY() + 180, 50, 50);
	// Label
	envDLabel.setBounds(transform.getX() + 50, transform.getY() + 170, 50, 15);
	envDLabel.setColour(Label::ColourIds::textColourId, Colour(38, 50, 56));
	envDLabel.setJustificationType(Justification::centred);
	envDLabel.setFont(Font(12, Font::bold));
	envDLabel.setText("D", NotificationType::dontSendNotification);
	editor->addAndMakeVisible(&envDLabel);

	// -------------
	// Env S
	// -------------
	// Params
	envSSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	envSSlider.setRange(0.0, 1.0, 0.01);
	envSSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	envSSlider.setPopupDisplayEnabled(true, true, editor);
	envSSlider.setTextValueSuffix(" Amp Sustain");
	envSSlider.setValue(0.75);
	// Actually add it
	editor->addAndMakeVisible(&envSSlider);
	// Sizing
	envSSlider.setBounds(transform.getX() + 100, transform.getY() + 180, 50, 50);
	// Label
	envSLabel.setBounds(transform.getX() + 100, transform.getY() + 170, 50, 15);
	envSLabel.setColour(Label::ColourIds::textColourId, Colour(38, 50, 56));
	envSLabel.setJustificationType(Justification::centred);
	envSLabel.setFont(Font(12, Font::bold));
	envSLabel.setText("S", NotificationType::dontSendNotification);
	editor->addAndMakeVisible(&envSLabel);

	// -------------
	// Env R
	// -------------
	// Params
	envRSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	envRSlider.setRange(10, 5000, 1);
	envRSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	envRSlider.setPopupDisplayEnabled(true, true, editor);
	envRSlider.setTextValueSuffix(" msec Release");
	envRSlider.setValue(50);
	// Actually add it
	editor->addAndMakeVisible(&envRSlider);
	// Sizing
	envRSlider.setBounds(transform.getX() + 150, transform.getY() + 180, 50, 50);
	// Label
	envRLabel.setBounds(transform.getX() + 150, transform.getY() + 170, 50, 15);
	envRLabel.setColour(Label::ColourIds::textColourId, Colour(38, 50, 56));
	envRLabel.setJustificationType(Justification::centred);
	envRLabel.setFont(Font(12, Font::bold));
	envRLabel.setText("R", NotificationType::dontSendNotification);
	editor->addAndMakeVisible(&envRLabel);
}

double CuttleFish::HUD_Oscillator::getWaveTable()
{
	return waveTableSlider.getValue();
}


double CuttleFish::HUD_Oscillator::getEnvA()
{
	return envASlider.getValue();
}


double CuttleFish::HUD_Oscillator::getEnvD()
{
	return envDSlider.getValue();
}


double CuttleFish::HUD_Oscillator::getEnvS()
{
	return envSSlider.getValue();
}


double CuttleFish::HUD_Oscillator::getEnvR()
{
	return envRSlider.getValue();
}
