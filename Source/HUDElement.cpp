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

HUDElement::HUDElement()
{
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

void CuttleFish::HUDElement::makeVisibleInEditor()
{
	makeFrameVisibleInEditor();
	makeControlsVisibleInEditor();
}

void CuttleFish::HUDElement::makeFrameVisibleInEditor()
{
	bool isGenerator = false;
	bool isEffect = false;

	if (CuttleFish::Generator *generator = dynamic_cast<CuttleFish::Generator*>(cuttleElements[0])) {
		isGenerator = true;
	}

	else if (CuttleFish::Effect *effect = dynamic_cast<CuttleFish::Effect*>(cuttleElements[0])) {
		isEffect = true;
	}

	editor->addAndMakeVisible(&frame);
	editor->addAndMakeVisible(&title);
	editor->addAndMakeVisible(&moveButton);
	editor->addAndMakeVisible(&bottom);
	editor->addAndMakeVisible(&outputButton);

	if (isEffect) {
		editor->addAndMakeVisible(&inputButton);
	}
}

void CuttleFish::HUDElement::setBounds()
{
	setFrameBounds();
	setControlBounds();
}

void CuttleFish::HUDElement::setFrameBounds()
{
	bool isGenerator = false;
	bool isEffect = false;

	if (CuttleFish::Generator *generator = dynamic_cast<CuttleFish::Generator*>(cuttleElements[0])) {
		isGenerator = true;
	}

	else if (CuttleFish::Effect *effect = dynamic_cast<CuttleFish::Effect*>(cuttleElements[0])) {
		isEffect = true;
	}

	// Title
	title.setBounds(transform.getX(), transform.getY(), transform.getWidth(), 30);

	// Frame
	frame.setBounds(transform.getX(), transform.getY(), transform.getWidth(), transform.getHeight());

	// Move Button
	moveButton.setBounds(transform.getX(), transform.getY(), 30, 30);

	// Bottom
	bottom.setBounds(transform.getX(), transform.getY() + transform.getHeight() - 40, transform.getWidth(), 40);

	// Input and Output Button
	if (isEffect) {
		inputButton.setBounds(transform.getX() + transform.getWidth() * 1 / 3 - 15, transform.getY() + transform.getHeight() - 35, 30, 30);
		outputButton.setBounds(transform.getX() + transform.getWidth() * 2 / 3 - 15, transform.getY() + transform.getHeight() - 35, 30, 30);
	}
	else {
		outputButton.setBounds(transform.getX() + transform.getWidth() * 1 / 2 - 15, transform.getY() + transform.getHeight() - 35, 30, 30);
	}
}

void CuttleFish::HUDElement::buttonClicked(Button * btn)
{
	if (btn->getName() == "InputButton") {
		editor->setConnectionInput(cuttleElements[0]->id);
	}

	if (btn->getName() == "OutputButton") {
		editor->setConnectionOutput(cuttleElements[1]->id);
	}
}

void CuttleFish::HUDElement::mouseDrag(const MouseEvent & event)
{
	Point<int> diff = event.getPosition();

	juce::Rectangle<int> newPos = transform + diff - dragStart;

	if (positionIsLegal(newPos)) {
		transform = newPos;
		editor->repaint();
	}

	setBounds();
}

void CuttleFish::HUDElement::mouseDown(const MouseEvent & event)
{
	dragStart = event.getPosition();
}

void CuttleFish::HUDElement::setEditor(CuttleFishAudioProcessorEditor * e)
{
	editor = e;
}

Line<float> CuttleFish::HUDElement::getOutgoingLine()
{
	return cuttleElements[0]->getOutgoingLine();
}

bool CuttleFish::HUDElement::hasOutgoingLine()
{
	return cuttleElements[0]->hasOutgoingLine();
}

Point<float> CuttleFish::HUDElement::getOutputPosition()
{
	float buttonWidth = outputButton.getWidth();
	return outputButton.getPosition().toFloat() + Point<float>(buttonWidth / 2, buttonWidth / 2);
}

Point<float> CuttleFish::HUDElement::getInputPosition()
{
	float buttonWidth = inputButton.getWidth();
	return inputButton.getPosition().toFloat() + Point<float>(buttonWidth / 2, buttonWidth / 2);
}

bool CuttleFish::HUDElement::positionIsLegal(juce::Rectangle<int> pos)
{
	// Left border (including master volume slider)
	if (pos.getX() < 60) {
		return false;
	}

	// Right border
	if (pos.getX() + pos.getWidth() > editor->getBounds().getWidth() - 40) {
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
	bool isGenerator = false;
	bool isEffect = false;

	if (CuttleFish::Generator *generator = dynamic_cast<CuttleFish::Generator*>(cuttleElements[0])) {
		isGenerator = true;
	}

	else if (CuttleFish::Effect *effect = dynamic_cast<CuttleFish::Effect*>(cuttleElements[0])) {
		isEffect = true;
	}

	// --------------
	// Frame
	// --------------
	frame.setColour(Label::ColourIds::outlineColourId, Colour(29, 33, 37));
	frame.setColour(Label::ColourIds::backgroundColourId, Colour(247, 247, 247));
	frame.setText("", NotificationType::dontSendNotification);

	// --------------
	// Title
	// --------------
	// generator color
	if (isGenerator) {
		title.setColour(Label::ColourIds::textColourId, Colour(171, 255, 176));
	}

	// effect color
	else if (isEffect) {
		title.setColour(Label::ColourIds::textColourId, Colour(168, 231, 255));
	}

	title.setColour(Label::ColourIds::backgroundColourId, Colour(29, 33, 37));
	title.setJustificationType(Justification::centred);
	title.setFont(Font(16, Font::bold));
	title.setText(cuttleElements[0]->getName().toUpperCase(), juce::NotificationType::dontSendNotification);

	// --------------
	// Move Button
	// --------------
	moveButton.setColour(TextButton::ColourIds::textColourOffId, Colour(230, 230, 230));
	moveButton.setColour(TextButton::ColourIds::buttonColourId, Colour(29, 33, 37));
	moveButton.setButtonText("M");
	moveButton.setName("MoveButton");
	moveButton.addMouseListener(this, false);

	// --------------
	// Bottom
	// --------------
	// generator color
	bottom.setColour(Label::ColourIds::backgroundColourId, Colour(60, 60, 60));
	bottom.setColour(Label::ColourIds::outlineColourId, Colour(29, 33, 37));
	bottom.setText("", juce::NotificationType::dontSendNotification);


	// --------------
	// Input Button
	// --------------
	if (isEffect) {
		inputButton.setColour(TextButton::ColourIds::textColourOffId, Colour(30, 30, 30));
		inputButton.setColour(TextButton::ColourIds::buttonColourId, Colour(171, 255, 176));
		inputButton.setButtonText("I");
		inputButton.setName("InputButton");
		inputButton.addListener(this);
	}

	// --------------
	// Output Button
	// --------------
	outputButton.setColour(TextButton::ColourIds::textColourOffId, Colour(30, 30, 30));
	outputButton.setColour(TextButton::ColourIds::buttonColourId, Colour(168, 231, 255));
	outputButton.setButtonText("O");
	outputButton.setName("OutputButton");
	outputButton.addListener(this);
}
