// c Maxim Urschumzew 2014

#include "stdafx.h"
#include "ConsoleService.h"

using namespace std;

int main()
{
	std::cout << "Hallo und tschuess und wieder hallo ;)" << std::endl;

	string text = string();
	std::getline(cin, text);

	SOIA::ConsoleManager* service = new SOIA::ConsoleManager();
	service->write();
	service->write();

	return 0;
}
