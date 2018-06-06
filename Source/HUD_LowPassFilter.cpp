/*
  ==============================================================================

    HUD_LowPassHilter.cpp
    Created: 2 Jun 2018 8:41:01pm
    Author:  Phalcon

  ==============================================================================
*/

#include "HUD_LowPassFilter.h"

using namespace CuttleFish;

HUD_LowPassFilter::HUD_LowPassFilter()
{
	setSize(200, 200);
}

CuttleFish::HUD_LowPassFilter::~HUD_LowPassFilter()
{
}

void CuttleFish::HUD_LowPassFilter::instantiateControls()
{
	// -------------
	// CUTOFF
	// -------------
	// Params
	cutoffSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	cutoffSlider.setRange(0, 1, 0.001);
	cutoffSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	cutoffSlider.setPopupDisplayEnabled(true, true, editor);
	cutoffSlider.setTextValueSuffix(" Hz Cutoff");
	cutoffSlider.setValue(1);
	setSliderColours(&cutoffSlider);
	// Label
	cutoffLabel.setColour(Label::ColourIds::textColourId, Colour(38, 50, 56));
	cutoffLabel.setJustificationType(Justification::centred);
	cutoffLabel.setFont(Font(12, Font::bold));
	cutoffLabel.setText("Cutoff", NotificationType::dontSendNotification);
}

void CuttleFish::HUD_LowPassFilter::setControlBounds()
{
	// Cutoff
	cutoffSlider.setBounds(transform.getX() + 40, transform.getY() + 45, 120, 120);
	cutoffLabel.setBounds(transform.getX() + 40, transform.getY() + 35, 120, 15);
}

void CuttleFish::HUD_LowPassFilter::makeControlsVisibleInEditor()
{
	editor->addAndMakeVisible(&cutoffSlider);
	editor->addAndMakeVisible(&cutoffLabel);
}

double CuttleFish::HUD_LowPassFilter::getCutoff()
{
	return cutoffSlider.getValue();
}