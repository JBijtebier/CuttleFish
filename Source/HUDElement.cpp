/*
  ==============================================================================

    HUDElement.cpp
    Created: 1 Jun 2018 6:57:01pm
    Author:  Phalcon

  ==============================================================================
*/

#include "HUDElement.h"
#include "CuttleElement.h"

using namespace CuttleFish;

HUDElement::HUDElement(AudioProcessorEditor *e)
{
	editor = e;
	setPosition(50, 50);
}

HUDElement::~HUDElement()
{
}

void CuttleFish::HUDElement::instantiateUI()
{
	instantiateFrame();
	instantiateControls();
}

void HUDElement::setPosition(int x, int y) {
	transform.setPosition(x, y);
}

void HUDElement::setPosition(Point<int> pos) {
	transform.setPosition(pos);
}

void CuttleFish::HUDElement::setSize(int width, int height)
{
	transform.setSize(width, height);
}

void HUDElement::addCuttleElement(CuttleElement * elem)
{
	cuttleElements.push_back(elem);
}

void CuttleFish::HUDElement::instantiateFrame()
{
	// --------------
	// Title
	// --------------
	title.setBounds(transform.getX(), transform.getY(), transform.getWidth(), 30);
	title.setColour(Label::ColourIds::textColourId, Colour(225, 225, 225));
	title.setColour(Label::ColourIds::backgroundColourId, Colour(38, 50, 56));
	title.setJustificationType(Justification::centred);
	title.setFont(Font(20, Font::bold));
	title.setText(cuttleElements[0]->getName(), juce::NotificationType::dontSendNotification);
	editor->addAndMakeVisible(&title);

	// --------------
	// Frame
	// --------------
	frame.setBounds(transform.getX(), transform.getY(), transform.getWidth(), transform.getHeight());
	frame.setColour(Label::ColourIds::outlineColourId, Colour(38, 50, 56));
	frame.setText("", NotificationType::dontSendNotification);
	editor->addAndMakeVisible(&frame);
}
