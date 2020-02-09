#include "stdafx.h"
#include "TrafficLight.h"

TrafficLight::TrafficLight(Phase initialPhase) {
	this->phase = initialPhase;
}

void TrafficLight::nextPhase() {
	switch (this->phase) {
	case Red: {
		this->phase = Ready;
		break;
	}
	case Ready: {
		this->phase = Green;
		break;
	}
	case Green: {
		this->phase = Stopping;
		break;
	}
	case Stopping: {
		this->phase = Red;
		break;
	}
	default: { break; }
	}
}

