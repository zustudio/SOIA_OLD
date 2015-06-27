
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
#include "BackupTool.h"
#include "EquationTool.h"
using namespace Supervisor;

#include <iostream>

constexpr static const char TEST[] = "ABD";


int main()
{
	

	DialogueInterface* dialogue = new StdDialogue();
	RDialogue* rdialogue = new RDialogue(dialogue);
	RContainer* topCont = new RContainer(Range<int>(0, 999));
	SetTopContainer(topCont);
	RContainer* container = new RContainer(Range<int>(1000,1999));
	topCont->Register(container, "tools");
	container->Register(rdialogue, "consoledialogue");
	RWorkerTool* Console = new ConsoleWorker(RPointer<RDialogue>(rdialogue));
	container->Register(Console, "console");
	auto elementexplorer = new ElementExplorerTool(RPointer<RDialogue>(rdialogue));
	container->Register(elementexplorer, "elementexplorer");
	MathContainer* mathContainer = new MathContainer();
	container->Register(mathContainer, "mathContainer");
	auto equationTool = new REquationTool(RPointer<RDialogue>(rdialogue));
	equationTool->cmd_setmathcontainer(mathContainer);
	container->Register(equationTool, "equation");
	container->Register(new BackupTool(RPointer<RDialogue>(rdialogue)), "backup");

	//std::string arg = "console";
	//std::vector<VoidPointer> InArgs = {};

	//{
	//	std::vector<VoidPointer>& ref_args = InArgs;
	//	std::vector<VoidPointer> args = { arg };

	//	{
	//		VoidPointer defaultAtom = *GetAtomReflectionProvider()->GetReflection(TypeID::FromType<RElement*>())->StringToObject("");
	//		if (defaultAtom.GetTypeID() == TypeID::FromType<RPointer>())
	//		{
	//			defaultAtom = defaultAtom.CastAndDereference<RPointer>().Resolve();
	//		}
	//		//args.push_back(defaultAtom);
	//	}
	//	ref_args = args;
	//}


	/*elementexplorer->GetAttribute("cmd_element").CastAndDereference<FunctionInterface*>()->CorrectArgsAndExecute(InArgs);
	auto names = InArgs[1].CastAndDereference<RElement*>()->GetAttributeNames();
	dialogue->WriteLine(names[0]);*/



	Console->Start();
	Console->Join();

	SaveFile sf = SaveFile("RTool", true);
	sf.Content.push_back(VoidPointer(static_cast<RElement*>(Console)));
	sf.Write();

	auto strings = Console->GetAttributeNames();
	for (auto string : strings)
	{
		LOGSTATUS("Attribute is: " + string);
	}
	
	//Console->GetAttribute("cmd_Help").CastAndDereference<FunctionInterface*>()->Execute({});

	using T = std::vector<std::string>;


	Console->CreateReflection();

	auto argTypes = Console->GetAttribute("cmd_echo").CastAndDereference<FunctionInterface*>()->GetArgumentTypes();
	for (auto argType : argTypes)
	{
		dialogue->WriteLine("ArgType: " + argType.ToString());
	}
	Console->GetAttribute("cmd_Help").CastAndDereference<FunctionInterface*>()->Execute({});
	std::string input = "Hello!";
	Console->GetAttribute("test").CastAndDereference<FunctionInterface*>()->Execute({ VoidPointer(input) });
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
