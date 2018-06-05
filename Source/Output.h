/*
  ==============================================================================

    Output.h
    Created: 18 Apr 2018 1:07:54pm
    Author:  Phalcon

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

		bool hasSupplier();

		Line<float> getOutgoingLine() override;

		bool hasOutgoingLine() override;

	private:
		CuttleElement * supplier;
	};

}