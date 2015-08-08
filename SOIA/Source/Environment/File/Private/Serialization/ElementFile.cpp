
#include "Definitions.h"

#include "ElementFile.h"
using namespace Environment;

#include "TokenArity_Nullary.h"
#include "TokenArity_Binary.h"
#include "TokenArity_Parenthesis.h"
#include "LogProvider.h"

////////////////////////////////////////////////////////////////
// Init
ElementFile::ElementFile(Path const & InPath)
	: IOFile(InPath),
	ElementTokenizer(
	{
		TokenRule(std::regex("\n([A-Za-z0-9_:<>]+)\n"), std::make_shared<TokenArity_Parenthesis>(EParenthesisType::Start)),
		TokenRule(std::regex("(=)"), std::make_shared<TokenArity_Binary>()),
		TokenRule(std::regex("\t([A-Za-z0-9_]+)"), std::make_shared<TokenArity_Nullary>()),
		TokenRule(std::regex("([A-Za-z0-9_,;\\.]+)\n"), std::make_shared<TokenArity_Nullary>()),
		TokenRule(std::regex("(\n)"), std::make_shared<TokenArity_Parenthesis>(EParenthesisType::End))
	})
{

}

////////////////////////////////////////////////////////////////
// Writing
void ElementFile::WriteMultiple(std::vector<RElement*> InElements, EElementSelectionMode InSelectionMode)
{
	for (RElement* element : InElements)
	{
		WriteSingle(element, InSelectionMode);
	}
}

void ElementFile::WriteSingle(RElement * InElement, EElementSelectionMode InSelectionMode)
{
	GetOutStream() << InElement->GetClass()->GetType().ToString() << '\n';

	std::vector<ObjectMirror*> const & attributes = InElement->GetAttributes();
	for (auto attribute : attributes)
	{
		std::string attributeName = attribute->GetName();
		VoidPointer p_attributeContent = attribute->Get();
		std::string attributeContent = GetAtomReflectionProvider()->GetReflection(p_attributeContent.GetTypeID())->ObjectToString(p_attributeContent);
		GetOutStream() << '\t' <<  attributeName << "= " << attributeContent << '\n';
	}
	GetOutStream() << '\n';
}



////////////////////////////////////////////////////////////////
// Reading
std::vector<RElement*> ElementFile::ReadMultiple(int InCount)
{
	std::vector<RElement*> elements = std::vector<RElement*>(InCount);
	RElement* element = nullptr;

	element = ReadSingle();
	while (element && InCount--)
	{
		elements.push_back(element);
		element = ReadSingle();
	}

	return elements;
}

RElement * ElementFile::ReadSingle()
{
	RElement* result = nullptr;
	std::list<Token*> tokens;
	bool success = ElementTokenizer.Tokenize(&GetInStream(), TokenRule(std::regex("\n\n"), std::make_shared<TokenArity_Nullary>()), tokens);

	Token* typeString = *tokens.begin();
	std::vector<Token*> attributeAssignments = typeString->GetSubTokenVector();

	if (success)
	{
		RClass* elementClass = GetElementReflectionProvider()->GetClass(TypeID(typeString->Text));
		result = elementClass->GetDefaultObject();

		for (Token* attributeAssignment : attributeAssignments)
		{
			Token* attributeName = attributeAssignment->GetSubTokenVector()[0];
			Token* attributeContent = attributeAssignment->GetSubTokenVector()[1];

			ObjectMirror* attributeMirror = result->GetAttribute(attributeName->Text);
			VoidPointer* p_newAttribute = GetAtomReflectionProvider()->GetReflection(attributeMirror->ObjectType())->StringToObject(attributeContent->Text);

			attributeMirror->SetIfTypesMatch(*p_newAttribute);
		}
	}

	return result;
}
