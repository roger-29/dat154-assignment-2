#include "stdafx.h"

#if 0
#include "TrafficLight.h"



class TrafficLight
{
	enum Phase {
		Red,
		Prepare,
		Green,
		Stopping
	}

public:
	TrafficLight();
	void nextPhase();
	int draw();

	Phase phase;
};



TrafficLight::TrafficLight() {
	this->phase = Red;
}

void TrafficLight::nextPhase() {
	switch(this->phase) {
	case Red: {
		this->phase = Prepare;
		break;
	}
	case Prepare: {
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
	default: {break; }
	}
}

#endif // 0