/*
  ==============================================================================

	CuttleElement.h
	Created: 17 Apr 2018 10:44:45pm
	Author:  Phalcon

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

namespace CuttleFish {

	class HUDElement;

	class CuttleElement {
	public:

		CuttleElement(int elementId);

		virtual juce::String getName() = 0;

		virtual double getSignal() = 0;

		void setHUDElement(HUDElement* elem);

		int id;

	protected:
		HUDElement* hudelement;
	};

}

/*
	==========================================================
	ELEMENT BASED DESIGN PLAN:

	## Hierarchy:

	CuttleElement -> Generator / Effect / Controller / Output

	Generator -> Oscillator, ...
	Effect -> Flanger, Filter, ...
	Controller -> FlatController / InputController

	FlatController -> LFO, ...
	InputController -> Envelope, ... (uses MIDI Input)

	Output -> 1 instance of output element that is "last in the chain"

	## Design

	- Maintain a list of: all elements, all generators, all inputcontrollers

	startNote -> set triggers, levels, frequencies in generators and inputcontrollers
	stopNote -> set triggers in generators and inputcontrollers
	renderNextBlock -> output.getSupplier().getSignal();

	getSignal() on an effect invokes getSignal on that effect's supplier
	controllers and generators return the signal without needing a supplier (so they always start the chain)


	==========================================================
*/