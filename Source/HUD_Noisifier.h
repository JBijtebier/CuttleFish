/*
  ==============================================================================

    HUD_Noisifier.h
    Created: 6 Jun 2018 8:35:45pm
    Author:  Phalcon

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "HUDElement.h"

namespace CuttleFish {

	class HUD_Noisifier : public HUDElement {
	public:
		HUD_Noisifier();
		~HUD_Noisifier();

		void instantiateControls() override;
		void setControlBounds() override;
		void removeControlsFromEditor() override;
		void makeControlsVisibleInEditor() override;

		double getAmount();

	private:
		Slider amountSlider;
		Label amountLabel;
	};

}
