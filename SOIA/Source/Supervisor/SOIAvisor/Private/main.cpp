
#include "Definitions.h"

#include "SaveFile.h"
#include "StdDialogue.h"
#include "Testing.h"
#include "LinearFunction.h"
#include "Window.h"
#include "LogProvider.h"
using namespace Environment;

#include "RTool.h"
using namespace Supervisor;

#include <iostream>

constexpr static const char TEST[] = "ABD";




int main()
{
	RTool tool = RTool(new StdDialogue());

	SaveFile sf = SaveFile("RTool", true);
	sf.Content.push_back((RElement*)&tool);
	sf.Write();

	auto strings = tool.GetAttributeNames();
	for (auto string : strings)
	{
		LOGSTATUS("Attribute is: " + string);
	}
	
	tool.GetAttribute("cmd_Help_Interface").CastAndDereference<FunctionInterface*>()->Execute({});

	using T = std::vector<std::string>;

	tool.CreateReflection();

	tool.cmd_Help_Interface->Execute({});


	X a;
	a.Go<1>();

	auto myWin = SO::Window("Hello World!! :)", pxPoint(1000, 300));
	myWin.Open();
	
	std::string Read;
	std::getline(std::cin, Read);

	std::cout << "hello world ;)" << std::endl;
	std::cout << "result of 1 + 3 is " << ZABS::Math::LinearFunction::get_f(3.0, { -1, 2 });
	return 0;
}