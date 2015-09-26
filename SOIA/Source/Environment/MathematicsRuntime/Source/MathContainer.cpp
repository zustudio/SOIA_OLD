
#include "Definitions.h"

#include "MathContainer.h"
using namespace Environment;

#include "DefinitionSet.h"
#include "Constant.h"
#include "Variable.h"
#include "MR_Function.h"
#include "OP_Add.h"
#include "MR_AppliedFunction.h"
#include "OP_Divide.h"
#include "OP_GreaterThan.h"
#include "OP_Select.h"
#include "OP_Multiply.h"
#include "OP_Substract.h"


#include "GlobalLogger.h"
#include "TokenArity_Binary.h"
#include "TokenArity_Nullary.h"
#include "TokenArity_Parenthesis.h"

MathContainer::MathContainer()
	: RContainer(Range<int>(1000, 10000000)),
	MathTokenizer(Tokenizer(
	{
		TokenRule(Parenthesis,		std::regex("(\\()"), std::make_shared<TokenArity_Parenthesis>(EParenthesisType::Start)),
		TokenRule(Parenthesis,		std::regex("(\\))"), std::make_shared<TokenArity_Parenthesis>(EParenthesisType::End)),
		TokenRule(FunctionName,		std::regex("([a-zA-Z_]+)\\("), std::make_shared<TokenArity_Parenthesis>(EParenthesisType::Start)),
		TokenRule(VarName,			std::regex("([a-zA-Z_]+)"), std::make_shared<TokenArity_Nullary>()),
		TokenRule(Number,			std::regex("([0-9]+)"), std::make_shared<TokenArity_Nullary>()),
		TokenRule(MultiplyDivide,	std::regex("([\\*/])"), std::make_shared<TokenArity_Binary>()),
		TokenRule(AddSubstract,		std::regex("([\\+-])"), std::make_shared<TokenArity_Binary>()),
		TokenRule(Assignment,		std::regex("(=)"), std::make_shared<TokenArity_Binary>())
	}))
{
	NULLConstant = new Constant(0);
	Register(NULLConstant, "NULL");
	FuncCache = new FunctionCache();
}

DynamicMathFunction* MathContainer::ParseString(std::string InString)
{
	DynamicMathFunction* function = nullptr;

	std::list<Token*> tokenlist;
	bool success = MathTokenizer.Tokenize(InString, tokenlist);

	if (tokenlist.size() != 1)
		LOG("Tokenization of '" + InString + "' resulted in " + std::to_string(tokenlist.size()) + " main tokens. Should always be 1.", Logger::Severity::Error);
	else
	{
		Token* token = *tokenlist.begin();
		Value* value = CreateValue(token);
		function = new DynamicMathFunction(this, value);
	}

	return function;
}

Value* MathContainer::CreateValue(Token * InToken)
{
	// load subtokens
	std::vector<Token*> subTokens = InToken->GetSubTokenVector();

	// apply this function recursively to subtokens
	std::vector<RPointer<Value>> subValues;
	for (Token* subToken : subTokens)
	{
		subValues.push_back(RPointer<Value>(CreateValue(subToken)));
	}

	// create new value
	Value* value = nullptr;
	std::string name = "";
	bool bDoNotRegister = false;
	switch (InToken->RuleIdentifier)
	{
	case Parenthesis:
		value = subValues[0].RawPointer();
		bDoNotRegister = true;
		break;
	case FunctionName:
		// if something is being assigned to the function token
		if (InToken->GetParentToken()
			&& InToken->GetParentToken()->RuleIdentifier == Assignment
			&& InToken->ContainerIteratorSet->Current == InToken->ContainerIteratorSet->Begin)
		{
			// check whether the general function form is used, or a special value
			if (subTokens[0]->RuleIdentifier == VarName)
			{
				std::vector<RPointer<Variable>> parameters;
				// check parameters of function and create corresponding variables
				for (int index_subToken = 0; index_subToken < subTokens.size(); ++index_subToken)
				{
					Variable* parameter = dynamic_cast<Variable*>(subValues[index_subToken].RawPointer());
					parameters.push_back(parameter);
				}
				value = new MR_Function(GetElement<Value>("NULL"), parameters);
				name = InToken->Text;
			}
			else
			{
				// find function and create new specialised function
				MR_Function* function = GetElement<MR_Function>(InToken->Text);
				if (function)
				{
					value = new MR_AppliedFunction(function, subValues);
				}
			}

		}
		else
		{
			// else create new calculation operation
			MR_Function* function = GetElement<MR_Function>(InToken->Text);
			if (function)
			{
				value = new MR_AppliedFunction(function, subValues);
			}
		}
		break;
	case VarName:
		value = GetElement<Value>(InToken->Text);
		if (value)
		{
			bDoNotRegister = true;
		}
		else
		{
			value = new Variable();
			name = InToken->Text;
		}
		break;
	case Number:
		value = new Constant(GlobalAtomConverterProvider()
			->GetConverter(TypeID::FromType<double>())
			->StringToObject(InToken->Text)
			->CastAndDereference<double>());
		break;
	case MultiplyDivide:
		if (InToken->Text == "*")
			value = new OP_Multiply(subValues);
		else if (InToken->Text == "/")
			value = new OP_Divide(subValues);
		break;
	case AddSubstract:
		if (InToken->Text == "+")
			value = new OP_Add(subValues);
		else if (InToken->Text == "-")
			value = new OP_Substract(subValues);
		break;
	case Assignment:
		if (subTokens[0]->RuleIdentifier == VarName)
		{
			Variable* variable = GetElement<Variable>(subTokens[0]->Text);
			variable->MakeConstant(Calculate(subValues[1].RawPointer(), {}));
			value = variable;
			bDoNotRegister = true;
		}
		else if (subValues[0]->GetClass() == MR_AppliedFunction::StaticClass())
		{
			MR_AppliedFunction* specialisedFunction = static_cast<MR_AppliedFunction*>(subValues[0].RawPointer());
			DefinitionSet EmptyDefinitionSet;
			specialisedFunction->ApplyAsSpecialValue(subValues[1]->Calculate(&EmptyDefinitionSet));
			value = specialisedFunction;
			bDoNotRegister = true;
		}
		else if (subTokens[0]->RuleIdentifier == FunctionName)
		{
			MR_Function* function = GetElement<MR_Function>(subTokens[0]->Text);
			function->SetBody(subValues[1]);
			value = function;
			bDoNotRegister = true;
		}
		break;
	default:
		break;
	}

	// register new value
	if (!bDoNotRegister)
	{
		Register(value, name);
		CacheStatus = ECacheStatus::Dirty;
	}
	return value;
}

double MathContainer::Calculate(Value * InValue, std::vector<double> const & InArguments)
{
	PrepareCache();
	std::vector<RPointer<Value>> tempArgumentConstants;
	for (double argument : InArguments)
	{
		tempArgumentConstants.push_back(new Constant(argument));
	}
	DefinitionSet emptyDefinitionSet;
	return MR_AppliedFunction(InValue, tempArgumentConstants).Calculate(&emptyDefinitionSet);
}

void MathContainer::PrepareCache()
{
	if (CacheStatus == ECacheStatus::Dirty)
	{
		std::vector<Value*> values = GetAllElements<Value>();
		for (Value* value : values)
		{
			value->PrepareCache();
		}
		CacheStatus = ECacheStatus::Valid;
	}
}



//double MathContainer::CalculateValue(const ElementID &InID)
//{
//	Value* element = GetElement<Value>(InID);
//	if (element)
//	{
//		return element->Calculate(GetAllElements<Value>());
//	}
//	return 35505;
//}
//double MathContainer::CalculateValue(const std::string& InName)
//{
//	Value* element = GetElement<Value>(InName);
//	if (element)
//	{
//		return element->Calculate(GetAllElements<Value>());
//	}
//	return 35505;
//}
//
//void MathContainer::SetValueName(const ElementID &InID, const std::string &InName)
//{
//	RElement* element = GetElement<Value>(InID);
//	element->GetName() = InName;
//}