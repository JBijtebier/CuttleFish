/*
  ==============================================================================

    Generator.h
    Created: 18 Apr 2018 12:57:56pm
    Author:  Phalcon

  ==============================================================================
*/

#pragma once
#include "CuttleElement.h"

namespace CuttleFish {

	class Generator : public CuttleElement {
	public:
		Generator(int elementId);

		virtual void startNote(double noteLevel, double noteFrequency) = 0;
		virtual void releaseNote() = 0;
		virtual bool isClear() = 0;

		void setSuccessor(CuttleElement *newSuccessor);
		CuttleElement * getSuccessor();
		bool hasSuccessor();

		Line<float> getOutgoingLine() override;
		bool hasOutgoingLine() override;

	private:
		CuttleElement * successor;
	};

}

