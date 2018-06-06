/*
  ==============================================================================

    HUD_HighPassFilter.h
    Created: 6 Jun 2018 4:47:29pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "HUDElement.h"

namespace CuttleFish {

	class HUD_HighPassFilter : public HUDElement {
	public:
		HUD_HighPassFilter();
		~HUD_HighPassFilter();

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

