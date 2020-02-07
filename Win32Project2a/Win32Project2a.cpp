
#include "stdafx.h"
#include <stdlib.h>
#include <algorithm>
#include <list>

#include "Constants.h"
#include "Main.h"
#include "Car.h"
#include "Draw.h"
#include "Shapes.h"
#include "Colors.h"

// Constants
#define MAX_LOADSTRING 100


#define IDC_MYICON 2
#define IDD_DAT154ASSIGNMENT2_DIALOG 102
#define IDS_APP_TITLE 103
#define IDD_ABOUTBOX 103
#define IDM_ABOUT 104
#define IDM_EXIT 105
#define IDI_ETC 107
#define IDI_SMALL 108
#define IDC_ETC 109
#define IDR_MAINFRAME 128
#define IDD_DIALOG1 129
#define IDC_EDIT1 1000
#define IDC_STATIC -1

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

using namespace Colors;


//Graphics

int LIGHTS_STATE = 0;

int LIGHT_RED = 0;
int LIGHT_READY = 1;
int LIGHT_GREEN = 2;
int LIGHT_STOPPING = 3;

int LIGHT_1_X = 550;
int LIGHT_1_Y = 10;

int LIGHT_2_X = 550;
int LIGHT_2_Y = 415;

void DrawCars(HDC* hdc, std::list<Car> cars, std::list<Car>::iterator it) {
	for (it = cars.begin(); it != cars.end(); ++it) {
		Rect(hdc, it->GetX(), it->GetY(), it->GetX() + 25, it->GetY() + 25, RED);
		Rect(hdc, it->GetX(), it->GetY(), it->GetX() + 25, it->GetY() + 25, RED);
	}
}

void drawLightsWithCommonState(HDC* hdc, int x1, int y1, int x2, int y2, int lightState) {
	switch (lightState) {
	case 0: {
		DrawTrafficLight(hdc, x1, y1, LIGHT_RED);
		DrawTrafficLight(hdc, x2, y2, LIGHT_GREEN);
		break;
	}
	case 1: {
		DrawTrafficLight(hdc, x1, y1, LIGHT_RED);
		DrawTrafficLight(hdc, x2, y2, LIGHT_STOPPING);
		break;
	}
	case 2: {
		DrawTrafficLight(hdc, x1, y1, LIGHT_READY);
		DrawTrafficLight(hdc, x2, y2, LIGHT_RED);
		break;
	}
	case 3: {
		DrawTrafficLight(hdc, x1, y1, LIGHT_GREEN);
		DrawTrafficLight(hdc, x2, y2, LIGHT_READY);
		break;
	}
	case 4: {
		DrawTrafficLight(hdc, x1, y1, LIGHT_STOPPING);
		DrawTrafficLight(hdc, x2, y2, LIGHT_RED);
		break;
	}
	case 5: {
		DrawTrafficLight(hdc, x1, y1, LIGHT_RED);
		DrawTrafficLight(hdc, x2, y2, LIGHT_READY);
		break;
	}
	default:
		break;
	}
};

int light = 0;
int changeLight = 0;
int pw;
int pn;
WCHAR dialogText[4];


std::list<Car> cars;
std::list<Car>::iterator it;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_ETC, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ETC));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ETC));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_ETC);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SetTimer(hWnd, 0, 30, (TIMERPROC)NULL);
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		drawLightsWithCommonState(&hdc, LIGHT_1_X, LIGHT_1_Y, LIGHT_2_X, LIGHT_2_Y, light);
		
		DrawRoads(&hdc);
		DrawCars(&hdc, cars, it);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_TIMER:
	{
		int i = rand() % 100;
		if (i > 100 - pw) {
			cars.push_front(Car(10, rand() % 80 + 285, false));
		}
		if (i > 100 - pn) {
			cars.push_front(Car(rand() % 80 + 655, 10, true));
		}
		if (changeLight == 1770) {
			light = (light + 1) % 6;
			InvalidateRect(hWnd, 0, true);
		}
		for (it = cars.begin(); it != cars.end(); ++it) {
			if (it->GetY() > 775 || it->GetX() > 1410) {
				cars.erase(it);
				break;
			}
			auto it2 = it;
			it2++;

			if (it->GetDrivingSouth()) {
				auto next = std::find_if(it2, cars.end(), [](auto& c) {return c.GetDrivingSouth(); });
				if (next != end(cars) && it->GetDrivingSouth()) {
					if (it->GetY() + 28 >= next->GetY()) {
						continue;
					}
				}
				if (light == 3 || light == 4) {
					it->Move();
					InvalidateRect(hWnd, 0, true);
				}
				else {
					if (it->GetY() < 240 || it->GetY() > 290) {
						it->Move();
						InvalidateRect(hWnd, 0, true);
					}
				}
			}
			else {
				auto next = std::find_if(it2, end(cars), [](auto& c) {return !c.GetDrivingSouth(); });
				if (next != end(cars) && !it->GetDrivingSouth()) {
					if (it->GetX() + 28 >= next->GetX()) {
						continue;
					}
				}
				if (light == 0 || light == 1) {
					it->Move();
					InvalidateRect(hWnd, 0, true);
				}
				else {
					if (it->GetX() < 610 || it->GetX() > 660) {
						it->Move();
						InvalidateRect(hWnd, 0, true);
					}
				}
			}
		}
		changeLight = (changeLight + 30) % 1800;
	}
	break;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
	{
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)DlgProc);
		InvalidateRect(hWnd, 0, true);
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_LEFT:
			pw--;
			break;
		case VK_RIGHT:
			pw++;
			break;
		case VK_UP:
			pn++;
			break;
		case VK_DOWN:
			pn--;
			break;
		default:
			break;
		}
	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



LRESULT CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			GetDlgItemText(hDlg, IDC_EDIT1, dialogText, 4);
			EndDialog(hDlg, LOWORD(wParam));
			pw = (int)dialogText[0] - 48;
			pn = (int)dialogText[2] - 48;
			return TRUE;
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, LOWORD(wParam));
		return TRUE;
	}

	return FALSE;
}