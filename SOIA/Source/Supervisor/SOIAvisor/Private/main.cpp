
#include "Definitions.h"

#include "SaveFile.h"
#include "StdDialogue.h"
#include "Testing.h"
#include "LinearFunction.h"
#include "Window.h"
#include "LogProvider.h"
using namespace Environment;

#include "RTool.h"
#include "RContainer.h"
#include "ConsoleWorker.h"
#include "ElementExplorerTool.h"
using namespace Supervisor;

#include <iostream>

constexpr static const char TEST[] = "ABD";




int main()
{
	DialogueInterface* dialogue = new StdDialogue();
	RContainer topCont = RContainer(Range<int>(0, 10000000));
	RContainer container = RContainer(Range<int>(0,1000));
	topCont.Register(&container, "toolcontainer");
	RWorkerTool* Console = new ConsoleWorker(dialogue);
	container.Register(Console, "console");
	container.Register(new ElementExplorerTool(dialogue), "elementexplorer");

	Console->Start();
	Console->Join();

	SaveFile sf = SaveFile("RTool", true);
	sf.Content.push_back((RElement*)Console);
	sf.Write();

	auto strings = Console->GetAttributeNames();
	for (auto string : strings)
	{
		LOGSTATUS("Attribute is: " + string);
	}
	
	//Console->GetAttribute("cmd_Help").CastAndDereference<FunctionInterface*>()->Execute({});

	using T = std::vector<std::string>;


	Console->CreateReflection();


	Console->GetAttribute("cmd_Help").CastAndDereference<FunctionInterface*>()->Execute({});
	std::string input = "Hello!";
	Console->GetAttribute("test").CastAndDereference<FunctionInterface*>()->Execute({ input });
	LOG(input, Logger::Severity::Warning);

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