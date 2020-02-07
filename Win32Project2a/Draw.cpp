#include <stdlib.h>
#include <algorithm>
#include <list>


#include "Shapes.h"
#include "stdafx.h"
#include "Car.h"

/*
  TrafficLight states
  0 - red
  1 - ready
  2 - green
  3 - stopping
*/
// DRAWtrafficlight(550, 10)

void Rect(HDC*, int, int, int, int, COLORREF);
void Circle(HDC*, int, int, int, int, COLORREF);

const COLORREF WHITE = RGB(255, 255, 255);
const COLORREF RED = RGB(255, 0, 0);
const COLORREF YELLOW = RGB(255, 255, 0);
const COLORREF GREEN = RGB(0, 255, 0);
const COLORREF BLUE = RGB(0, 0, 255);
const COLORREF GREY = RGB(192, 192, 192);
const COLORREF DARKGREY = RGB(105, 105, 105);
const COLORREF BLACK = RGB(0, 0, 0);

void DrawTrafficLight(HDC* hdc, int x, int y, int state) {

	// Dimensions
	int left = x;
	int top = y;

	int right = left + 90;
	int bottom = top + 250;

	int firstTop = top + 10;
	int secondTop = top + 90;
	int thirdTop = top + 170;

	// Draw background
	Rect(hdc, left, top, right, bottom, BLACK);

	// Draw lights with color based on light state
	switch (state) {
	case 0:
	{
		Circle(hdc, left + 10, firstTop, right - 10, top + 80, RED);
		Circle(hdc, left + 10, secondTop, right - 10, top + 160, GREY);
		Circle(hdc, left + 10, thirdTop, right - 10, top + 240, GREY);
		break;
	}

	case 1:
	{
		Circle(hdc, left + 10, firstTop, right - 10, top + 80, RED);
		Circle(hdc, left + 10, secondTop, right - 10, top + 160, YELLOW);
		Circle(hdc, left + 10, thirdTop, right - 10, top + 240, GREY);
		break;
	}
	case 2:
	{
		Circle(hdc, left + 10, firstTop, right - 10, top + 80, GREY);
		Circle(hdc, left + 10, secondTop, right - 10, top + 160, GREY);
		Circle(hdc, left + 10, thirdTop, right - 10, top + 240, GREEN);
		break;
	}

	case 3:
	{
		Circle(hdc, left, firstTop, right - 10, top + 80, GREY);
		Circle(hdc, left, secondTop, right - 10, top + 160, YELLOW);
		Circle(hdc, left, thirdTop, right - 10, top + 240, GREY);
		break;
	}
	}
};

void DrawRoads(HDC* hdc) {
	Rect(hdc, 650, 10, 775, 675, DARKGREY);
	Rect(hdc, 10, 280, 1410, 405, DARKGREY);

	Rect(hdc, 662, 10, 664, 675, WHITE);
	Rect(hdc, 761, 10, 763, 675, WHITE);

	Rect(hdc, 10, 292, 1410, 294, WHITE);
	Rect(hdc, 10, 391, 1410, 393, WHITE);
}


