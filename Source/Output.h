/*
  ==============================================================================

    Output.h
    Created: 18 Apr 2018 1:07:54pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#pragma once
#include "CuttleElement.h"

namespace CuttleFish {

	class Output : public CuttleElement {
	public:
		Output(int elementId);
		~Output();

		static Point<int> position;

		juce::String getName() override;

		double getSignal() override;

		void setSupplier(CuttleElement *newSupplier);
		CuttleElement * getSupplier();
		bool hasSupplier();

		Line<float> getOutgoingLine() override;

		bool hasOutgoingLine() override;

	private:
		CuttleElement * supplier;
	};

}