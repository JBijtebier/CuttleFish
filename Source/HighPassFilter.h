/*
  ==============================================================================

    HighPassFilter.h
    Created: 6 Jun 2018 4:47:21pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#pragma once

#include "Effect.h"
#include "maximilian.h"

namespace CuttleFish {

	class HighPassFilter : public Effect {
	public:
		HighPassFilter(int elementId);
		~HighPassFilter();

		juce::String getName() override;

		double getSignal() override;

		double cutoff;

	private:

		maxiFilter filter;
	};

}