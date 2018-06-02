/*
  ==============================================================================

    HUD_Oscillator.h
    Created: 1 Jun 2018 7:12:18pm
    Author:  Phalcon

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "HUDElement.h"

namespace CuttleFish {

	class HUD_Oscillator : public HUDElement {
	public:
		HUD_Oscillator(CuttleFishAudioProcessorEditor *e);
		~HUD_Oscillator();
		
		void instantiateControls() override;
		void setControlBounds() override;

		double getWaveTable();
		double getEnvA();
		double getEnvD();
		double getEnvS();
		double getEnvR();

	private:
		Slider waveTableSlider;
		Slider envASlider;
		Slider envDSlider;
		Slider envSSlider;
		Slider envRSlider;
		Label waveTableLabel;
		Label envALabel;
		Label envDLabel;
		Label envSLabel;
		Label envRLabel;
	};

}

