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
	setBounds();
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

void CuttleFish::HUDElement::setBounds()
{
	setFrameBounds();
	setControlBounds();
}

void CuttleFish::HUDElement::setFrameBounds()
{
	// Title
	title.setBounds(transform.getX(), transform.getY(), transform.getWidth(), 30);

	// Frame
	frame.setBounds(transform.getX(), transform.getY(), transform.getWidth(), transform.getHeight());

	// Move Button
	moveButton.setBounds(transform.getX(), transform.getY(), 30, 30);
}

void CuttleFish::HUDElement::mouseDrag(const MouseEvent & event)
{
	Point<int> diff = event.getPosition();

	Rectangle<int> newPos = transform + diff - dragStart;

	if (positionIsLegal(newPos)) {
		transform = newPos;
	}

	setBounds();
}

void CuttleFish::HUDElement::mouseDown(const MouseEvent & event)
{
	dragStart = event.getPosition();
}

bool CuttleFish::HUDElement::positionIsLegal(juce::Rectangle<int> pos)
{
	// Left border (including master volume slider)
	if (pos.getX() < 60) {
		return false;
	}

	// Right border
	if (pos.getX() + pos.getWidth() > editor->getBounds().getWidth()) {
		return false;
	}

	// Top border
	if (pos.getY() < 0) {
		return false;
	}

	// Bottom border
	if (pos.getY() + pos.getHeight() > editor->getBounds().getHeight()) {
		return false;
	}

	return true;
}

void CuttleFish::HUDElement::instantiateFrame()
{
	// --------------
	// Title
	// --------------
	title.setColour(Label::ColourIds::textColourId, Colour(225, 225, 225));
	title.setColour(Label::ColourIds::backgroundColourId, Colour(38, 50, 56));
	title.setJustificationType(Justification::centred);
	title.setFont(Font(20, Font::bold));
	title.setText(cuttleElements[0]->getName(), juce::NotificationType::dontSendNotification);
	editor->addAndMakeVisible(&title);

	// --------------
	// Frame
	// --------------
	frame.setColour(Label::ColourIds::outlineColourId, Colour(38, 50, 56));
	frame.setText("", NotificationType::dontSendNotification);
	editor->addAndMakeVisible(&frame);

	// --------------
	// Move Button
	// --------------
	moveButton.setColour(TextButton::ColourIds::textColourOffId, Colour(225, 225, 225));
	moveButton.setColour(TextButton::ColourIds::buttonColourId, Colour(38, 50, 56));
	moveButton.setButtonText("M");
	moveButton.setName("MoveButton");
	moveButton.addMouseListener(this, false);
	editor->addAndMakeVisible(&moveButton);
}
