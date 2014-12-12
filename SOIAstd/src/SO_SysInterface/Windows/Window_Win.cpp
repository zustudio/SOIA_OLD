// window class for Windows OS

#include <iostream>
#include <windows.h>
#include <wingdi.h>
#include "fColor.h"
#include "Window_Win.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// callback definition
LRESULT CALLBACK SO::Window_Win::WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
{
	Window_Win *c = (Window_Win*)GetWindowLong(window, GWLP_USERDATA);

	switch (msg)
	{
	case WM_DESTROY:
		std::cout << "\ndestroying window\n";
		PostQuitMessage(0);
		return 0L;
	case WM_SIZE:		//same as paint
	case WM_PAINT:
		c->props.bDirty = true;
		return DefWindowProc(window, msg, wp, lp);
	case WM_LBUTTONDOWN:
		//std::cout << "\nmouse left button down at (" << LOWORD(lp) << ',' << HIWORD(lp) << ")\n";
		// fall thru
	
	default:
		//std::cout << '.';
		return DefWindowProc(window, msg, wp, lp);
	}
}



//////////////////////////////////////////////////////////////////////////////////////
// init
SO::Window_Win::Window_Win() : Window_Base()
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
	wc.lpfnWndProc = (WNDPROC)WindowProcedure;
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
			CW_USEDEFAULT, CW_USEDEFAULT, props.size.X, props.size.Y,
			NULL, NULL, GetModuleHandle(0), NULL);

		SetWindowLong(hwnd, GWLP_USERDATA, (long long)this);		//set (this*) for getting in WindowProcedure

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

		if (props.bDirty)
		{
			SetVars();
			Clear();
			Draw();

			props.bDirty = false;
		}
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
	if (props.size.X != rect.right)
		std::cout << "#";
	props.size.X = rect.right;
	props.size.Y = rect.bottom;
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
	::Rectangle(hdc, a.X, a.Y, a.X + b.X, a.Y + b.Y);
	::ReleaseDC(hwnd, hdc);
}

//////////////////////////////////////////////////////////////////////////
// sub drawing
COLORREF SO::Window_Win::getColor(fColor* color)
{
	return RGB(int(color->R*255), int(color->G*255), int(color->B*255));
}
void SO::Window_Win::Clear()
{
	HDC hdc;
	COLORREF backgroundColor;
	hdc = ::GetDC(hwnd);
	::SetDCBrushColor(hdc, getColor(props.backColor));
	::Rectangle(hdc, 0, 0, props.size.X, props.size.Y);
	::SetDCBrushColor(hdc, getColor(props.frontColor));
}