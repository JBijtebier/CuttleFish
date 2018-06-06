/*
  ==============================================================================

    HUD_PowerShaper.cpp
    Created: 6 Jun 2018 9:07:16pm
    Author:  Phalcon

  ==============================================================================
*/

#include "HUD_PowerShaper.h"

using namespace CuttleFish;

HUD_PowerShaper::HUD_PowerShaper()
{
	setSize(200, 200);
}

CuttleFish::HUD_PowerShaper::~HUD_PowerShaper()
{
}

void CuttleFish::HUD_PowerShaper::instantiateControls()
{
	// -------------
	// POWER
	// -------------
	// Params
	powerSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	powerSlider.setRange(0.05, 5, 0.01);
	powerSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	powerSlider.setPopupDisplayEnabled(true, true, editor);
	powerSlider.setTextValueSuffix(" Power");
	powerSlider.setValue(1);
	setSliderColours(&powerSlider);
	// Label
	powerLabel.setColour(Label::ColourIds::textColourId, Colour(38, 50, 56));
	powerLabel.setJustificationType(Justification::centred);
	powerLabel.setFont(Font(12, Font::bold));
	powerLabel.setText("Power", NotificationType::dontSendNotification);
}

void CuttleFish::HUD_PowerShaper::setControlBounds()
{
	// Cutoff
	powerSlider.setBounds(transform.getX() + 40, transform.getY() + 45, 120, 120);
	powerLabel.setBounds(transform.getX() + 40, transform.getY() + 35, 120, 15);
}

void CuttleFish::HUD_PowerShaper::makeControlsVisibleInEditor()
{
	editor->addAndMakeVisible(&powerSlider);
	editor->addAndMakeVisible(&powerLabel);
}

double CuttleFish::HUD_PowerShaper::getPower()
{
	return powerSlider.getValue();
}