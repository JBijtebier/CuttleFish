/*
  ==============================================================================

    SynthSound.cpp
    Created: 27 Mar 2018 8:41:58pm
    Author:  Jens Bijtebier

  ==============================================================================
*/

#include "SynthSound.h"

bool SynthSound::appliesToNote(int midiNoteNumber) {
	return true;
}

bool SynthSound::appliesToChannel(int midiChannel) {
	return true;
}