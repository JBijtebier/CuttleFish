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
		bool hasSupplier();

	protected:
		CuttleElement * supplier;
	};

}

