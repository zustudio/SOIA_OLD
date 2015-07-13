
#include "Definitions.h"

#include "ConsoleWorker.h"
using namespace Supervisor;
using namespace Environment;

#include "RContainer.h"
#include <regex>

ConsoleWorker::ConsoleWorker(const RPointer<RDialogue>& InDialogue)
	: BaseType(InDialogue),
	InputTokenizer(
	{
		TokenRule("([a-zA-Z0-9_]+)", new TokenCollapseNone),
		TokenRule("(\\()", new TokenCollapseParenthesis(EParenthesisType::Start)),
		TokenRule("(\\))", new TokenCollapseParenthesis(EParenthesisType::End))
	}),
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

		Token* OutResult = nullptr;
		std::vector<VoidPointer> OutArguments;
		InputTokenizer.Tokenize(input, OutResult);
		ExecuteCommands(OutResult, OutArguments);


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

bool ConsoleWorker::ExecuteCommands(Token* Input, std::vector<Environment::VoidPointer>& OutArguments)
{
	std::vector<Token*> subTokens = Input->GetSubTokens();
	std::vector<std::string> inputs;
	std::vector<VoidPointer> inputPointers;
	int n = subTokens.size();
	for (int i = 0; i < n; i++)
	{
		std::string singleInputString = subTokens[i]->Text;
		bool bisFunction = subTokens[i]->GetSubTokens().size() > 0;
		if (bisFunction)
		{
			std::vector<VoidPointer> outArguments;
			ExecuteCommands(subTokens[i], outArguments);

			int requestedArgument = 0; // TODO: parse number from input
			if (requestedArgument >= outArguments.size())
			{
				Dialogue->WriteLine("Command '" + subTokens[i]->GetSubTokens()[0]->Text + "' does not have an argument no. "
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
			// remove quotes
			if (singleInputString[singleInputString.size() - 1] == '\"')
				singleInputString = std::string(singleInputString.begin() + 1, singleInputString.end() - 1);

			inputs.push_back(singleInputString);
			inputPointers.push_back(VoidPointer(new std::string(singleInputString)));
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
			if (!p_attribute.IsNullPointer() && p_attribute.CastTo<RFunction*>())
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
		std::vector<RTool*> targets = Container->GetElementsWithAttribute<RTool, RFunction*>(functionName);
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
		target->GetAttribute(functionName).CastAndDereference<RFunction*>()->CorrectArgsAndExecute(InOutArguments);
		return true;
	}
}

std::vector<std::string> ConsoleWorker::GetArguments(const std::string & InInput)
{
	std::string input = InInput;
	std::regex pattern("(\"(.*?)\"|[a-zA-Z0-9_]+:?|\\d*\\(.+\\))");
	auto result = std::smatch();

	std::vector<std::string> inputs;
	std::vector<VoidPointer> inputPointers;
	while (std::regex_search(input, result, pattern))
	{

	}

	return std::vector<std::string>();
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

