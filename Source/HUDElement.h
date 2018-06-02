/*
  ==============================================================================

    HUDElement.h
    Created: 1 Jun 2018 6:57:01pm
    Author:  Phalcon

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <vector>

namespace CuttleFish {

	class CuttleElement;

	class HUDElement : MouseListener {
	public:
		HUDElement(AudioProcessorEditor *e);
		~HUDElement();

		void setPosition(int x, int y);

		void setPosition(Point<int> pos);

		void setSize(int width, int height);

		void addCuttleElement(CuttleElement *elem);

		// Instantiation
		void instantiateUI();
		void instantiateFrame();
		virtual void instantiateControls() = 0;

		// Bounds
		void setBounds();	
		void setFrameBounds();
		virtual void setControlBounds() = 0;

		// Mouse Listener
		void mouseDrag(const MouseEvent &event) override;
		void mouseDown(const MouseEvent &event) override;

	protected:
		bool positionIsLegal(juce::Rectangle<int> pos);
		void setSliderColours(Slider* slider);

		juce::Rectangle<int> transform;
		std::vector<CuttleElement *> cuttleElements;
		AudioProcessorEditor *editor;
		Point<int> dragStart;

		Label title;
		Label frame;
		TextButton moveButton;
	};

}