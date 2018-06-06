/*
  ==============================================================================

    HUD_PowerShaper.h
    Created: 6 Jun 2018 9:07:16pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "HUDElement.h"

namespace CuttleFish {

	class HUD_PowerShaper : public HUDElement {
	public:
		HUD_PowerShaper();
		~HUD_PowerShaper();

		void instantiateControls() override;
		void setControlBounds() override;
		void makeControlsVisibleInEditor() override;

		double getPower();

	private:
		Slider powerSlider;
		Label powerLabel;
	};

}
