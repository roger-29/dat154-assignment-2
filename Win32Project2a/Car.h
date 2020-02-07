#pragma once

#define MOVE_SPEED 3;

class Car
{
public:
	bool drivingSouth;
	int x, y;

	Car(int x, int _y, bool _goingSouth);
	
	void Move();

	bool GetDrivingSouth(){return drivingSouth;}
	int GetX()	{		return x;	}
	int GetY()	{	return y;	}
};