#include "stdafx.h"
#include "TrafficLightSystem.h"

/*
	Model for a two light intersection
*/

TrafficLightSystem::TrafficLightSystem() {
	this->state = 0;
}

void TrafficLightSystem::nextPhase() {
	this->state = state + 1 % 6;
}