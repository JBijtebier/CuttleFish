/*
  ==============================================================================

    HUDElement.cpp
    Created: 1 Jun 2018 6:57:01pm
    Author:  Phalcon

  ==============================================================================
*/

#include "HUDElement.h"
#include "CuttleElement.h"
#include "Generator.h"
#include "Output.h"
#include "Effect.h"

using namespace CuttleFish;

HUDElement::HUDElement(AudioProcessorEditor *e)
{
	editor = e;
	setPosition(100, 100);
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
	if (pos.getY() < 45) {
		return false;
	}

	// Bottom border
	if (pos.getY() + pos.getHeight() > editor->getBounds().getHeight()) {
		return false;
	}

	return true;
}

void CuttleFish::HUDElement::setSliderColours(Slider * slider)
{
	slider->setColour(Slider::thumbColourId, Colour(168, 231, 255));
}

void CuttleFish::HUDElement::instantiateFrame()
{
	// --------------
	// Frame
	// --------------
	frame.setColour(Label::ColourIds::outlineColourId, Colour(29, 33, 37));
	frame.setColour(Label::ColourIds::backgroundColourId, Colour(247, 247, 247));
	frame.setText("", NotificationType::dontSendNotification);
	editor->addAndMakeVisible(&frame);

	// --------------
	// Title
	// --------------
	// generator color
	if (CuttleFish::Generator *generator = dynamic_cast<CuttleFish::Generator*>(cuttleElements[0])) {
		title.setColour(Label::ColourIds::textColourId, Colour(171, 255, 176));
	}

	// effect color
	else if (CuttleFish::Effect *effect = dynamic_cast<CuttleFish::Effect*>(cuttleElements[0])) {
		title.setColour(Label::ColourIds::textColourId, Colour(168, 231, 255));
	}

	// output color
	else if (CuttleFish::Output *newOutput = dynamic_cast<CuttleFish::Output*>(cuttleElements[0])) {
		title.setColour(Label::ColourIds::textColourId, Colour(200, 180, 255));
	}

	title.setColour(Label::ColourIds::backgroundColourId, Colour(29, 33, 37));
	title.setJustificationType(Justification::centred);
	title.setFont(Font(16, Font::bold));
	title.setText(cuttleElements[0]->getName().toUpperCase(), juce::NotificationType::dontSendNotification);
	editor->addAndMakeVisible(&title);

	// --------------
	// Move Button
	// --------------
	moveButton.setColour(TextButton::ColourIds::textColourOffId, Colour(230, 230, 230));
	moveButton.setColour(TextButton::ColourIds::buttonColourId, Colour(29, 33, 37));
	moveButton.setButtonText("M");
	moveButton.setName("MoveButton");
	moveButton.addMouseListener(this, false);
	editor->addAndMakeVisible(&moveButton);
}
