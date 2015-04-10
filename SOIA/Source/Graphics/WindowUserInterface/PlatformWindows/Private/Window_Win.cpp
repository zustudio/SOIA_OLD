// window class for Windows OS

#include <iostream>
#include "fColor.h"

#include "Window_Win.h"

/////////////////////////////////////////////////////////////////////////////////////////////
// callback definition
LRESULT CALLBACK SO::Window_Win::WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
{
	Window_Win *c = (Window_Win*)GetWindowLongPtr(window, GWLP_USERDATA);

	switch (msg)
	{
	case WM_DESTROY:
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
SO::Window_Win::Window_Win(const std::string &NewTitle, const pxPoint &size) : Window_Base(NewTitle, size)
{
	hwnd = 0;
}
SO::Window_Win::~Window_Win()
{

}

//////////////////////////////////////////////////////////////////////////////////////
// start
int SO::Window_Win::Open()
{
	const char* const myclass = props.title->c_str();
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

	UnregisterClass(wc.lpszClassName, wc.hInstance);
	if (RegisterClassEx(&wc))
	{
		hwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			myclass,
			props.title->c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, props.size.X, props.size.Y,
			NULL, NULL, GetModuleHandle(0), NULL);

		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);		//set (this*) for getting in WindowProcedure

		if (hwnd)
		{
			ShowWindow(hwnd, SW_SHOWDEFAULT);

			props.bOpen = true;
			do
			{
				Tick();
			}
			while (props.bOpen);
		}
		else
		{
			return -1;
		}
	}
	return 0;
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
		props.bOpen = false;
	}
}

void SO::Window_Win::SetVars()
{
	RECT rect;
	::GetClientRect(hwnd, &rect);
	props.size.X = rect.right;
	props.size.Y = rect.bottom;
}

////////////////////////////////////////////////////////////////
// drawing functions
void SO::Window_Win::Refresh()
{
	Draw();
}
void SO::Window_Win::pxDrawText(pxPoint Loc, const std::string &text)
{
	HDC hdc;
	Win32_PrepText(hdc);
	::TextOut(hdc, Loc.X, Loc.Y, const_cast<char *>(text.c_str()), strlen(text.c_str()));
	Win32_EndDrawing(hdc);
}
void SO::Window_Win::pxDrawLine(pxPoint a, pxPoint b)
{
	HDC hdc;
	Win32_PrepDrawing(hdc);
	::MoveToEx(hdc, a.X, a.Y, NULL);
	::LineTo(hdc, b.X, b.Y);
	Win32_EndDrawing(hdc);
}
void SO::Window_Win::pxDrawRect(pxPoint a, pxPoint b)
{
	HDC hdc;
	Win32_PrepDrawing(hdc);
	::Rectangle(hdc, a.X, a.Y, a.X + b.X, a.Y + b.Y);
	Win32_EndDrawing(hdc);
}

//////////////////////////////////////////////////////////////////////////
// sub drawing
COLORREF SO::Window_Win::getColor(fColor* color)
{
	return RGB(int(color->R*255), int(color->G*255), int(color->B*255));
}
void SO::Window_Win::Clear()
{
	fColor *oldFront = props.frontColor;
	props.frontColor = props.backColor;

	HDC hdc;
	Win32_PrepDrawing(hdc);
	::Rectangle(hdc, 0, 0, props.size.X, props.size.Y);
	Win32_EndDrawing(hdc);
	props.frontColor = oldFront;
}
