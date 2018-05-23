/*
  ==============================================================================

    LowPassFilter.h
    Created: 21 May 2018 9:58:00pm
    Author:  Phalcon

  ==============================================================================
*/

#pragma once

#include "Effect.h"
#include "maximilian.h"

namespace CuttleFish {

	class LowPassFilter : public Effect {
	public:
		LowPassFilter(int elementId);
		~LowPassFilter();

		juce::String getName() override;

		double getSignal() override;

		void instantiateUI() override;

		double cutoff;

	private:

		maxiFilter filter;
	};

}