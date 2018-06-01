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

	class HUDElement {
	public:
		HUDElement(AudioProcessorEditor *e);
		~HUDElement();

		void instantiateUI();

		void setPosition(int x, int y);

		void setPosition(Point<int> pos);

		void setSize(int width, int height);

		void addCuttleElement(CuttleElement *elem);

		virtual void instantiateControls() = 0;

		void instantiateFrame();

	protected:
		juce::Rectangle<int> transform;
		std::vector<CuttleElement *> cuttleElements;
		AudioProcessorEditor *editor;

		Label title;
		Label frame;
	};

}