#include "stdafx.h"
#include "TrafficLightSystem.h"

/*
	Model for a two light intersection
*/

TrafficLightSystem::TrafficLightSystem() {
	this->phase = 0;
}

void TrafficLightSystem::nextPhase() {
	this->phase = phase + 1 % 6;
}