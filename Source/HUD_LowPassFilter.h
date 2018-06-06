/*
  ==============================================================================

    HUD_LowPassHilter.h
    Created: 2 Jun 2018 8:41:01pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "HUDElement.h"

namespace CuttleFish {

	class HUD_LowPassFilter : public HUDElement {
	public:
		HUD_LowPassFilter();
		~HUD_LowPassFilter();

		void instantiateControls() override;
		void setControlBounds() override;
		void removeControlsFromEditor() override;
		void makeControlsVisibleInEditor() override;

		double getCutoff();

	private:
		Slider cutoffSlider;
		Label cutoffLabel;
	};

}

