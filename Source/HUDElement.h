/*
  ==============================================================================

    HUDElement.h
    Created: 1 Jun 2018 6:57:01pm
    Author:  Phalcon

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginEditor.h"
#include <vector>

namespace CuttleFish {

	class CuttleElement;

	class HUDElement : MouseListener, Button::Listener {
	public:
		HUDElement();
		~HUDElement();

		void setPosition(int x, int y);

		void setPosition(Point<int> pos);

		void setSize(int width, int height);

		void addCuttleElement(CuttleElement *elem);

		// Drawing
		void makeVisibleInEditor();
		void makeFrameVisibleInEditor();
		virtual void makeControlsVisibleInEditor() = 0;

		// Instantiation
		void instantiateUI();
		void instantiateFrame();
		virtual void instantiateControls() = 0;

		// Bounds
		void setBounds();	
		void setFrameBounds();
		virtual void setControlBounds() = 0;

		// Button Listener
		void buttonClicked(Button * btn) override;

		// Mouse Listener
		void mouseDrag(const MouseEvent &event) override;
		void mouseDown(const MouseEvent &event) override;

		void setEditor(CuttleFishAudioProcessorEditor *e);

	protected:
		bool positionIsLegal(juce::Rectangle<int> pos);
		void setSliderColours(Slider* slider);
		CuttleFishAudioProcessorEditor* editor;

		juce::Rectangle<int> transform;
		std::vector<CuttleElement *> cuttleElements;
		Point<int> dragStart;

		Label title;
		Label frame;
		Label bottom;
		TextButton moveButton;
		TextButton inputButton;
		TextButton outputButton;
	};

}