#include "stdafx.h"
#include "Window_Base.h"

using namespace SO;

///////////////////////////////////////////////////
// init
Window_Base::Window_Base()
{

}
Window_Base::~Window_Base()
{

}

///////////////////////////////////////////////////
// main
void Window_Base::Start()
{
	std::cout << "Window class: application compiled without window interface, exiting.";
}