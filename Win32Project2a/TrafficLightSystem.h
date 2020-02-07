#pragma once

class TrafficLightSystem {
	int phase;
public:
	TrafficLightSystem();
	void nextPhase();
	int getPhase() { return phase; };
};

