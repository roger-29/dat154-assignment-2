#include "stdafx.h"
#include "Car.h"

#define MOVE_SPEED 3;


Car::Car(int x, int _y, bool _goingSouth) {
	this->x = x;
	this->y = _y;
	this->drivingSouth = _goingSouth;
}

void Car::Move() {
	if (drivingSouth) {
		y = y + MOVE_SPEED;
	}
	else {
		x = x + MOVE_SPEED;
	}
}