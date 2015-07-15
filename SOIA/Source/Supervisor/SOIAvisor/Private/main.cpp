
#include "Definitions.h"

#include "FileSystemProvider.h"
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
#include "RWorkspaceTool.h"
using namespace Supervisor;

#include <iostream>

constexpr static const char TEST[] = "ABD";


int main()
{

	//TEST
	GetFileSystem()->GetExecutableDirectory().GetSubDirectories();

	//ENDTEST

	DialogueInterface* dialogue = new StdDialogue();
	RDialogue* rdialogue = new RDialogue(dialogue);
	RContainer* topCont = new RContainer(Range<int>(1, 999));
	topCont->GetID().Name = "Quantum";
	topCont->GetID().UniqueIdentifier = 0;
	SetTopContainer(topCont);
	RContainer* container = new RContainer(Range<int>(1000,1999));
	topCont->Register(container, "tools");
	container->Register(new RWorkspaceTool(RPointer<RDialogue>(rdialogue)), "workspace");
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


	/*elementexplorer->GetAttribute("cmd_element").CastAndDereference<RFunction*>()->CorrectArgsAndExecute(InArgs);
	auto names = InArgs[1].CastAndDereference<RElement*>()->GetAttributeNames();
	dialogue->WriteLine(names[0]);*/



	Console->Start();
	Console->Join();

	SaveFile sf = SaveFile("RTool", true);
	RElement* cast_console = static_cast<RElement*>(Console);
	sf.Content.push_back(VoidPointer(&cast_console, EMemoryType::Stack));
	sf.Write();

	auto strings = Console->GetAttributeNames();
	for (auto string : strings)
	{
		LOGSTATUS("Attribute is: " + string);
	}
	
	//Console->GetAttribute("cmd_Help").CastAndDereference<RFunction*>()->Execute({});
}
