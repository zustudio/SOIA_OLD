// testing

#include <iostream>
#include <windows.h>
#include "Window_Win.h"

using namespace SO;

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
Window_Win::Window_Win()
{
	
}
Window_Win::~Window_Win()
{

}

//////////////////////////////////////////////////////////////////////////////////////
// start
void Window_Win::Start()
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
		HWND hwnd = CreateWindowEx(
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

			conf.AddLoops(-1);
			Thread::Start();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
// loop
void Window_Win::Tick()
{
	MSG msg;
	if (GetMessage(&msg, 0, 0, 0))
	{
		DispatchMessage(&msg);
	}
	else
	{
		conf.Disable();
	}
}

