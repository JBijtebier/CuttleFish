/*
  ==============================================================================

    Noisifier.h
    Created: 6 Jun 2018 8:35:17pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#pragma once
#include "Effect.h"
#include "maximilian.h"

namespace CuttleFish {

	class Noisifier : public Effect {
	public:
		Noisifier(int elementId);
		~Noisifier();

		juce::String getName() override;

		double getSignal() override;

	private:
		Random rnd;
	};

}