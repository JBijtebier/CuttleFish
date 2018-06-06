/*
  ==============================================================================

    HUD_NoiseGenerator.h
    Created: 6 Jun 2018 7:55:28pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "HUDElement.h"

namespace CuttleFish {

	class HUD_NoiseGenerator : public HUDElement {
	public:
		HUD_NoiseGenerator();
		~HUD_NoiseGenerator();

		void instantiateControls() override;
		void setControlBounds() override;
		void makeControlsVisibleInEditor() override;

		double getEnvA();
		double getEnvD();
		double getEnvS();
		double getEnvR();

	private:
		Slider envASlider;
		Slider envDSlider;
		Slider envSSlider;
		Slider envRSlider;
		Label envALabel;
		Label envDLabel;
		Label envSLabel;
		Label envRLabel;
	};

}

