
#include "Definitions.h"

#include "TConsole.h"
using namespace Supervisor;
using namespace Environment;

#include "RContainer.h"
#include "GlobalLogger.h"
#include "TokenArity_Nullary.h"
#include "TokenArity_Parenthesis.h"

#include <regex>

TConsole::TConsole()
	: BaseType(),
	InputTokenizer(
	{
		TokenRule(std::regex("\"(.*)\""),			std::make_shared<TokenArity_Nullary>()),
		TokenRule(std::regex("([a-zA-Z0-9_\\.]+)"),	std::make_shared<TokenArity_Nullary>()),
		TokenRule(std::regex("(\\()"),				std::make_shared<TokenArity_Parenthesis>(EParenthesisType::Start)),
		TokenRule(std::regex("(\\))"),				std::make_shared<TokenArity_Parenthesis>(EParenthesisType::End))
	}),
	bExit(false)
{
	ReflectAttributes();
}

void TConsole::Main()
{
	ConfigureMainTool(&MainDialogue);

	std::string currentTarget;
	while (!bExit && !IsStopping())
	{
		std::string input;
		Dialogue->WriteLine("");
		Dialogue->Write("> ");
		Dialogue->GetNextLine(input);

		if (!input.empty())
		{

			std::list<Token*> OutResult;
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
			std::vector<TTool*> OutTools;
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
}

bool TConsole::ExecuteCommands(std::list<Token*> const & Input, std::vector<Environment::VoidPointer>& OutArguments)
{
	std::vector<Token*> tokens = std::vector<Token*>(Input.begin(), Input.end());
	std::vector<std::string> inputs;
	std::vector<VoidPointer> inputPointers;
	int n = tokens.size();
	for (int i = 0; i < n; i++)
	{
		std::string singleInputString = tokens[i]->Text;
		bool bisFunction = tokens[i]->GetSubTokens().size() > 0;
		if (bisFunction)
		{
			std::vector<VoidPointer> outArguments;
			bool subsuccess = ExecuteCommands(tokens[i]->GetSubTokens(), outArguments);
			if (!subsuccess)
				return subsuccess;
				

			int requestedArgument = 0; // TODO: parse number from input
			if (requestedArgument >= outArguments.size())
			{
				Dialogue->WriteLine("Command '" + tokens[i]->GetSubTokenVector()[0]->Text + "' does not have an argument no. "
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

bool TConsole::ExecuteCommand(const std::string& InTarget, std::string& InCommand, std::vector<Environment::VoidPointer>& InOutArguments)
{
	TTool* target = nullptr;
	std::string functionName;
	if (InTarget != "")
	{
		functionName = "cmd_" + InCommand;
		std::string targetName = InTarget;
		target = Container->GetElement<TTool>(targetName);
		if (target)
		{
			auto p_attribute = target->GetAttribute(functionName);
			if (p_attribute && p_attribute->Object().CastTo<RFunction*>())
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
		std::vector<TTool*> targets = Container->GetElementsWithAttribute<TTool, RFunction*>(functionName);
		if (targets.size() == 0)
			Dialogue->WriteLine("Could not find tool with function :" + functionName);
		else if (targets.size() > 1)
		{
			Dialogue->WriteLine("Function name is ambigious. Try to specify your target via: @target " + functionName + '\n'
				+ "Following target are available: ");
			for (auto target : targets)
			{
				Dialogue->WriteLine(target->GetName());
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
		bool success = target->GetAttribute(functionName)->Object().CastAndDereference<RFunction*>()->CorrectArgsAndExecute(InOutArguments);
		if (!success)
		{
			LOG("Command '" + functionName + "' returned false.", Logger::Severity::Warning);
		}
		return success;
	}
}

std::vector<std::string> TConsole::GetArguments(const std::string & InInput)
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

bool TConsole::cmd_exit()
{
	bExit = true;
	return true;
}

bool TConsole::cmd_echo(const std::string& InText)
{
	Dialogue->WriteLine(InText);
	return true;
}

