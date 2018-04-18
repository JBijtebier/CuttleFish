/*
  ==============================================================================

    SynthSound.h
    Created: 27 Mar 2018 8:41:58pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound {
	public:

		bool appliesToNote(int midiNoteNumber) override;

		bool appliesToChannel(int midiChannel) override;

	private:
};