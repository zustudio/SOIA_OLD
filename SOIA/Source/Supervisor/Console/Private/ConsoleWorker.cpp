
#include "Definitions.h"

#include "ConsoleWorker.h"
using namespace Supervisor;
using namespace Environment;

#include "RContainer.h"
#include <regex>

ConsoleWorker::ConsoleWorker(const RPointer<RDialogue>& InDialogue)
	: BaseType(InDialogue),
	bExit(false)
{
	ReflectAttributes();
}

void ConsoleWorker::Main()
{
	std::string currentTarget;
	while (!bExit && !IsStopping())
	{
		std::string input;
		Dialogue->WriteLine("");
		Dialogue->Write("> ");
		Dialogue->GetNextLine(input);

		std::vector<VoidPointer> arguments;

		ExecuteCommands(input, arguments);

		



		/*std::vector<std::string> args;

		int p_Last = 0;
		for (std::string::size_type p_Char = 0; p_Char < input.size(); p_Char++)
		{
			if (input[p_Char] == ' ' || input[p_Char] == '\n')
			{
				args.push_back(input.substr(p_Last, p_Char - p_Last));
				p_Last = p_Char + 1;
			}
		}
*/
		

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

bool ConsoleWorker::ExecuteCommands(const std::string& InInput, std::vector<Environment::VoidPointer>& OutArguments)
{
	//pattern ([a-zA-Z]+[ |:]?)
	//pattern |\\d+\\(.+\\)
	std::string input = InInput;
	std::regex pattern("([a-zA-Z.\"_]+:?|\\d*\\(.+\\))");
	auto result = std::smatch();
	
	std::vector<std::string> inputs;
	std::vector<VoidPointer> inputPointers;
	while(std::regex_search(input, result, pattern))
	{
		std::string singleInputString = result[1].str();
		input = result.suffix().str();
		std::regex functionPattern("(\\d*)\\((.+)\\)");
		auto functionPatternResult = std::smatch();
		bool bisFunction = std::regex_match(singleInputString, functionPatternResult, functionPattern);
		if (bisFunction)
		{
			int requestedArgument = std::atoi(functionPatternResult[1].str().c_str());
			std::string innerCommand = functionPatternResult[2].str();
			std::vector<VoidPointer> outArguments;
			ExecuteCommands(innerCommand, outArguments);

			if (requestedArgument >= outArguments.size())
			{
				Dialogue->WriteLine("Command '" + innerCommand + "' does not have an argument no. "
					+ std::to_string(requestedArgument) + " to retrieve.");
				return false;
			}
			inputPointers.push_back(outArguments[requestedArgument]);
		}
		else
		{
			// remove trailing whitespace
			if (singleInputString[singleInputString.size() - 1] == ' ')
				singleInputString = std::string(singleInputString.begin(), singleInputString.end() - 1);

			inputs.push_back(singleInputString);
			inputPointers.push_back(*new std::string(singleInputString));
		}
	}

	std::string target = "";
	std::string command = "";
	std::string input0 = inputs[0];
	if (input0[input0.size() - 1] == ':')
	{
		target = std::string(input0.begin(), input0.end() - 1);
		command = inputs[1];
		OutArguments = std::vector<VoidPointer>(inputPointers.begin() + 2, inputPointers.end());
	}
	else
	{
		command = input0;
		OutArguments = std::vector<VoidPointer>(inputPointers.begin() + 1, inputPointers.end());
	}
	return ExecuteCommand(target, command, OutArguments);
}

bool ConsoleWorker::ExecuteCommand(const std::string& InTarget, std::string& InCommand, std::vector<Environment::VoidPointer>& InOutArguments)
{
	RTool* target = nullptr;
	std::string functionName;
	if (InTarget != "")
	{
		functionName = "cmd_" + InCommand;
		std::string targetName = InTarget;
		target = Container->GetElement<RTool>(targetName);
		if (target)
		{
			auto p_attribute = target->GetAttribute(functionName);
			if (!p_attribute.IsNullPointer() && p_attribute.CastTo<FunctionInterface*>())
			{
				//targetArgs = std::vector<VoidPointer>(args.begin() + 2, args.end());
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
		functionName = "cmd_" + InCommand;
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
			//targetArgs = std::vector<VoidPointer>(args.begin() + 1, args.end());
		}
	}

	if (target == nullptr)
	{
		Dialogue->WriteLine("Could not find tool");
		return false;
	}
	else
	{
		target->GetAttribute(functionName).CastAndDereference<FunctionInterface*>()->CorrectArgsAndExecute(InOutArguments);
		return true;
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

