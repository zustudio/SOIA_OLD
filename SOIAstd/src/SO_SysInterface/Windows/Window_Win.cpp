// testing

#include <iostream>
#include <windows.h>
#include <wingdi.h>
#include "Window_Win.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// callback definition
LRESULT CALLBACK WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		std::cout << "\ndestroying window\n";
		PostQuitMessage(0);
		return 0L;
	case WM_LBUTTONDOWN:
		std::cout << "\nmouse left button down at (" << LOWORD(lp)
			<< ',' << HIWORD(lp) << ")\n";
		// fall thru
	default:
		std::cout << '.';
		return DefWindowProc(window, msg, wp, lp);
	}
}



//////////////////////////////////////////////////////////////////////////////////////
// init
SO::Window_Win::Window_Win()
{
	
}
SO::Window_Win::~Window_Win()
{

}

//////////////////////////////////////////////////////////////////////////////////////
// start
void SO::Window_Win::Start()
{
	std::cout << "hello world!\n";
	const char* const myclass = "myclass";
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WindowProcedure;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(0);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = myclass;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (RegisterClassEx(&wc))
	{
		hwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			myclass,
			"The title of my window",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
			NULL, NULL, GetModuleHandle(0), NULL);


		if (hwnd)
		{
			ShowWindow(hwnd, SW_SHOWDEFAULT);
			MSG msg;

			MThread.AddLoops(-1);
			Thread::Start();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// loop
void SO::Window_Win::Tick()
{
	MSG msg;
	if (GetMessage(&msg, 0, 0, 0))
	{
		DispatchMessage(&msg);

		pxPoint Loc = pxPoint(100, 100);
		std::string text = "hallo noch einmal";
		SetVars();
		pxDrawText(Loc, text);
		Draw();
	}
	else
	{
		MThread.Disable();
	}
}

void SO::Window_Win::SetVars()
{
	RECT rect;
	::GetClientRect(hwnd, &rect);
	size.X = rect.right;
	size.Y = rect.bottom;
}

////////////////////////////////////////////////////////////////
// drawing functions
void SO::Window_Win::pxDrawText(pxPoint Loc, const std::string &text)
{
	HDC hdc;
	hdc = ::GetDC(hwnd);
	::TextOut(hdc, Loc.X, Loc.Y, const_cast<char *>(text.c_str()), strlen(text.c_str()));
	::ReleaseDC(hwnd, hdc);
}
void SO::Window_Win::pxDrawLine(pxPoint a, pxPoint b)
{
	HDC hdc;
	hdc = ::GetDC(hwnd);
	::SetCursorPos(a.X, b.X);
	::LineTo(hdc, b.X, b.Y);
	::ReleaseDC(hwnd, hdc);
}
void SO::Window_Win::pxDrawRect(pxPoint a, pxPoint b)
{
	HDC hdc;
	hdc = ::GetDC(hwnd);
	::Rectangle(hdc, a.X, a.Y, b.X, b.Y);
	::ReleaseDC(hwnd, hdc);
}

