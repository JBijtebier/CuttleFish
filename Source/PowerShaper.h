/*
  ==============================================================================

    PowerShaper.h
    Created: 6 Jun 2018 9:06:56pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#pragma once
#include "Effect.h"
#include "maximilian.h"

namespace CuttleFish {

	class PowerShaper : public Effect {
	public:
		PowerShaper(int elementId);
		~PowerShaper();

		juce::String getName() override;

		double getSignal() override;

	private:
	};

}