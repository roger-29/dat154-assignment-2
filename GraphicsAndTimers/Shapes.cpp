#include "stdafx.h"
#include "Shapes.h"

void Rect(HDC* hdc, int left, int top, int right, int bottom, COLORREF color) {
	HBRUSH hBrush = CreateSolidBrush(color);
	HGDIOBJ hOrg = SelectObject(*hdc, hBrush);
	RECT rct;
	rct.left = left;
	rct.top = top;
	rct.right = right;
	rct.bottom = bottom;
	FillRect(*hdc, &rct, hBrush);
	SelectObject(*hdc, hOrg);
	DeleteObject(hBrush);
}

void Circle(HDC* hdc, int left, int top, int right, int bottom, COLORREF color) {
	HBRUSH hBrush = CreateSolidBrush(color);
	HGDIOBJ hOrg = SelectObject(*hdc, hBrush);
	Ellipse(*hdc, left, top, right, bottom);
	SelectObject(*hdc, hOrg);
	DeleteObject(hBrush);
}
