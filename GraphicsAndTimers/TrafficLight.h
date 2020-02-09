#pragma once

class TrafficLight {
	enum Phase {
		Red,
		Ready,
		Green,
		Stopping
	};

	Phase phase;
public:
	TrafficLight(Phase initialPhase);
	
	void nextPhase();
	
	Phase getPhase() { return phase; }
};
