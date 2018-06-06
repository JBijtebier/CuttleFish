/*
  ==============================================================================

    HUD_NoiseGenerator.cpp
    Created: 6 Jun 2018 7:55:45pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#include "HUD_NoiseGenerator.h"

using namespace CuttleFish;

HUD_NoiseGenerator::HUD_NoiseGenerator()
{
	setSize(200, 135);
}

CuttleFish::HUD_NoiseGenerator::~HUD_NoiseGenerator()
{
}

void CuttleFish::HUD_NoiseGenerator::instantiateControls()
{
	// -------------
	// Env A
	// -------------
	// Params
	envASlider.setSliderStyle(Slider::RotaryVerticalDrag);
	envASlider.setRange(10, 3000, 1);
	envASlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	envASlider.setPopupDisplayEnabled(true, true, editor);
	envASlider.setTextValueSuffix(" msec Attack");
	envASlider.setValue(25);
	setSliderColours(&envASlider);
	// Label
	envALabel.setColour(Label::ColourIds::textColourId, Colour(38, 50, 56));
	envALabel.setJustificationType(Justification::centred);
	envALabel.setFont(Font(12, Font::bold));
	envALabel.setText("A", NotificationType::dontSendNotification);

	// -------------
	// Env D
	// -------------
	// Params
	envDSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	envDSlider.setRange(10, 3000, 1);
	envDSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	envDSlider.setPopupDisplayEnabled(true, true, editor);
	envDSlider.setTextValueSuffix(" msec Decay");
	envDSlider.setValue(500);
	setSliderColours(&envDSlider);
	// Label
	envDLabel.setColour(Label::ColourIds::textColourId, Colour(38, 50, 56));
	envDLabel.setJustificationType(Justification::centred);
	envDLabel.setFont(Font(12, Font::bold));
	envDLabel.setText("D", NotificationType::dontSendNotification);

	// -------------
	// Env S
	// -------------
	// Params
	envSSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	envSSlider.setRange(0.0, 1.0, 0.001);
	envSSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	envSSlider.setPopupDisplayEnabled(true, true, editor);
	envSSlider.setTextValueSuffix(" Amp Sustain");
	envSSlider.setValue(0.75);
	setSliderColours(&envSSlider);
	// Label
	envSLabel.setColour(Label::ColourIds::textColourId, Colour(38, 50, 56));
	envSLabel.setJustificationType(Justification::centred);
	envSLabel.setFont(Font(12, Font::bold));
	envSLabel.setText("S", NotificationType::dontSendNotification);

	// -------------
	// Env R
	// -------------
	// Params
	envRSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	envRSlider.setRange(10, 3000, 1);
	envRSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	envRSlider.setPopupDisplayEnabled(true, true, editor);
	envRSlider.setTextValueSuffix(" msec Release");
	envRSlider.setValue(50);
	// Label
	envRLabel.setColour(Label::ColourIds::textColourId, Colour(38, 50, 56));
	envRLabel.setJustificationType(Justification::centred);
	envRLabel.setFont(Font(12, Font::bold));
	envRLabel.setText("R", NotificationType::dontSendNotification);
}

void CuttleFish::HUD_NoiseGenerator::setControlBounds()
{
	// Env A
	envASlider.setBounds(transform.getX() + 0, transform.getY() + 45, 50, 50);
	envALabel.setBounds(transform.getX() + 0, transform.getY() + 35, 50, 15);

	// Env D
	envDSlider.setBounds(transform.getX() + 50, transform.getY() + 45, 50, 50);
	envDLabel.setBounds(transform.getX() + 50, transform.getY() + 35, 50, 15);

	// Env S
	envSSlider.setBounds(transform.getX() + 100, transform.getY() + 45, 50, 50);
	envSLabel.setBounds(transform.getX() + 100, transform.getY() + 35, 50, 15);

	// Env R
	envRSlider.setBounds(transform.getX() + 150, transform.getY() + 45, 50, 50);
	envRLabel.setBounds(transform.getX() + 150, transform.getY() + 35, 50, 15);
}

void CuttleFish::HUD_NoiseGenerator::removeControlsFromEditor()
{
	editor->removeChildComponent(&envASlider);
	editor->removeChildComponent(&envALabel);
	editor->removeChildComponent(&envDSlider);
	editor->removeChildComponent(&envDLabel);
	editor->removeChildComponent(&envSSlider);
	editor->removeChildComponent(&envSLabel);
	editor->removeChildComponent(&envRSlider);
	editor->removeChildComponent(&envRLabel);
}

void CuttleFish::HUD_NoiseGenerator::makeControlsVisibleInEditor()
{
	editor->addAndMakeVisible(&envASlider);
	editor->addAndMakeVisible(&envALabel);
	editor->addAndMakeVisible(&envDSlider);
	editor->addAndMakeVisible(&envDLabel);
	editor->addAndMakeVisible(&envSSlider);
	editor->addAndMakeVisible(&envSLabel);
	editor->addAndMakeVisible(&envRSlider);
	editor->addAndMakeVisible(&envRLabel);
}

double CuttleFish::HUD_NoiseGenerator::getEnvA()
{
	return envASlider.getValue();
}


double CuttleFish::HUD_NoiseGenerator::getEnvD()
{
	return envDSlider.getValue();
}


double CuttleFish::HUD_NoiseGenerator::getEnvS()
{
	return envSSlider.getValue();
}


double CuttleFish::HUD_NoiseGenerator::getEnvR()
{
	return envRSlider.getValue();
}
