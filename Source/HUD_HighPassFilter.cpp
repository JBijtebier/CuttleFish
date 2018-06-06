/*
  ==============================================================================

    HUD_HighPassFilter.cpp
    Created: 6 Jun 2018 4:47:29pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#include "HUD_HighPassFilter.h"

using namespace CuttleFish;

HUD_HighPassFilter::HUD_HighPassFilter()
{
	setSize(200, 200);
}

CuttleFish::HUD_HighPassFilter::~HUD_HighPassFilter()
{
}

void CuttleFish::HUD_HighPassFilter::instantiateControls()
{
	// -------------
	// CUTOFF
	// -------------
	// Params
	cutoffSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	cutoffSlider.setRange(0, 1, 0.001);
	cutoffSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	cutoffSlider.setPopupDisplayEnabled(true, true, editor);
	cutoffSlider.setTextValueSuffix(" Cutoff");
	cutoffSlider.setValue(0);
	setSliderColours(&cutoffSlider);
	// Label
	cutoffLabel.setColour(Label::ColourIds::textColourId, Colour(38, 50, 56));
	cutoffLabel.setJustificationType(Justification::centred);
	cutoffLabel.setFont(Font(12, Font::bold));
	cutoffLabel.setText("Cutoff", NotificationType::dontSendNotification);
}

void CuttleFish::HUD_HighPassFilter::setControlBounds()
{
	// Cutoff
	cutoffSlider.setBounds(transform.getX() + 40, transform.getY() + 45, 120, 120);
	cutoffLabel.setBounds(transform.getX() + 40, transform.getY() + 35, 120, 15);
}

void CuttleFish::HUD_HighPassFilter::removeControlsFromEditor()
{
	editor->removeChildComponent(&cutoffSlider);
	editor->removeChildComponent(&cutoffLabel);
}

void CuttleFish::HUD_HighPassFilter::makeControlsVisibleInEditor()
{
	editor->addAndMakeVisible(&cutoffSlider);
	editor->addAndMakeVisible(&cutoffLabel);
}

double CuttleFish::HUD_HighPassFilter::getCutoff()
{
	return cutoffSlider.getValue();
}