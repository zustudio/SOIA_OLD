

#include "Add.h"
#include <iostream>

int main()
{
	std::cout << "hello world ;)" << std::endl;
	std::cout << "result of 1 + 3 is " << Add::Execute(3.0, 1.0);
	return 0;
}