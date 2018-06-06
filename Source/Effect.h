/*
  ==============================================================================

    Effect.h
    Created: 21 May 2018 9:56:12pm
    Author:  Phalcon

  ==============================================================================
*/

#pragma once
#include "CuttleElement.h"

namespace CuttleFish {

	class Effect : public CuttleElement {
	public:
		Effect(int elementId);

		void setSupplier(CuttleElement *newSupplier);
		CuttleElement * getSupplier();
		void setSuccessor(CuttleElement *newSuccessor);
		CuttleElement * getSuccessor();
		bool hasSupplier();
		bool hasSuccessor();

		Line<float> getOutgoingLine() override;
		bool hasOutgoingLine() override;

	protected:
		CuttleElement * supplier;
		CuttleElement * successor;
	};

}

