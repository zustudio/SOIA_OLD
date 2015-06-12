
#include "Definitions.h"

#include "ConsoleWorker.h"
using namespace Supervisor;

#include "RContainer.h"

ConsoleWorker::ConsoleWorker(DialogueInterface* InDialogue)
	: BaseType(InDialogue),
	bExit(false)
{
	ReflectAttributes();
}

void ConsoleWorker::Main()
{
	std::string currentTarget;
	while (!bExit)
	{
		std::string input;
		Dialogue->GetNextLine(input);

		input.push_back(' ');

		std::vector<std::string> args;

		int p_Last = 0;
		for (std::string::size_type p_Char = 0; p_Char < input.size(); p_Char++)
		{
			if (input[p_Char] == ' ' || input[p_Char] == '\n')
			{
				args.push_back(input.substr(p_Last, p_Char - p_Last));
				p_Last = p_Char + 1;
			}
		}

		RTool* target = nullptr;
		std::string functionName;
		std::vector<VoidPointer> targetArgs;
		if (args[0][0] == '@')
		{
			functionName = "cmd_" + args[1];
			std::string targetName = args[0].substr(1, args[0].size() - 1);
			target = Container->GetElement<RTool>(targetName);
			if (target)
			{
				auto p_attribute = target->GetAttribute(functionName);
				if (!p_attribute.IsNullPointer() && p_attribute.CastTo<FunctionInterface*>())
				{
					targetArgs = std::vector<VoidPointer>(args.begin() + 2, args.end());
				}
				else
				{
					target = nullptr;
				}
			}
			else
			{
				target = nullptr;
			}
		}
		else
		{
			functionName = "cmd_" + args[0];
			std::vector<RTool*> targets = Container->GetElementsWithAttribute<RTool, FunctionInterface*>(functionName);
			if (targets.size() == 0)
				Dialogue->WriteLine("Could not find tool with function :" + functionName);
			else if (targets.size() > 1)
			{
				Dialogue->WriteLine("Function name is ambigious. Try to specify your target via: @target " + functionName + '\n'
					+ "Following target are available: ");
				for (auto target : targets)
				{
					Dialogue->WriteLine(target->GetID().Name);
				}
			}
			else
			{
				target = targets[0];
				targetArgs = std::vector<VoidPointer>(args.begin() + 1, args.end());
			}
		}

		if (target == nullptr)
		{
			Dialogue->WriteLine("Could not find tool");
		}
		else
		{
			target->GetAttribute(functionName).CastAndDereference<FunctionInterface*>()->Execute(targetArgs);
		}

		/*bool result;
		std::vector<RTool*> OutTools;
		std::vector<RFunctionInterface*> OutFunctions;
		std::vector<Environment::VoidPointer> OutArgs;

		result = InterpretInput(args, OutTools, OutFunctions, OutArgs);

		if (result)
		{
			OutFunctions[0]->Execute(OutArgs);
		}*/


		if (input == "exit")
			bExit = true;
	}
}

bool ConsoleWorker::cmd_exit()
{
	bExit = true;
	return true;
}

bool ConsoleWorker::cmd_echo(const std::string& InText)
{
	Dialogue->WriteLine(InText);
	return true;
}