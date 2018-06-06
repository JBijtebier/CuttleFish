/*
  ==============================================================================

    HUD_Noisifier.cpp
    Created: 6 Jun 2018 8:35:45pm
    Author:  Phalcon

  ==============================================================================
*/

#include "HUD_Noisifier.h"

using namespace CuttleFish;

HUD_Noisifier::HUD_Noisifier()
{
	setSize(200, 200);
}

CuttleFish::HUD_Noisifier::~HUD_Noisifier()
{
}

void CuttleFish::HUD_Noisifier::instantiateControls()
{
	// -------------
	// AMOUNT
	// -------------
	// Params
	amountSlider.setSliderStyle(Slider::RotaryVerticalDrag);
	amountSlider.setRange(0, 1, 0.001);
	amountSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	amountSlider.setPopupDisplayEnabled(true, true, editor);
	amountSlider.setTextValueSuffix(" Amount");
	amountSlider.setValue(0.5);
	setSliderColours(&amountSlider);
	// Label
	amountLabel.setColour(Label::ColourIds::textColourId, Colour(38, 50, 56));
	amountLabel.setJustificationType(Justification::centred);
	amountLabel.setFont(Font(12, Font::bold));
	amountLabel.setText("Amount", NotificationType::dontSendNotification);
}

void CuttleFish::HUD_Noisifier::setControlBounds()
{
	// Cutoff
	amountSlider.setBounds(transform.getX() + 40, transform.getY() + 45, 120, 120);
	amountLabel.setBounds(transform.getX() + 40, transform.getY() + 35, 120, 15);
}

void CuttleFish::HUD_Noisifier::removeControlsFromEditor()
{
	editor->removeChildComponent(&amountSlider);
	editor->removeChildComponent(&amountLabel);
}

void CuttleFish::HUD_Noisifier::makeControlsVisibleInEditor()
{
	editor->addAndMakeVisible(&amountSlider);
	editor->addAndMakeVisible(&amountLabel);
}

double CuttleFish::HUD_Noisifier::getAmount()
{
	return amountSlider.getValue();
}