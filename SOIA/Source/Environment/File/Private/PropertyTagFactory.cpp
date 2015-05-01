
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/File/Public/PropertyTagFactory.h"
using namespace Environment;

#include <sstream>

////////////////////////////////////////////////////////////////
// Initializing
PropertyTagFactory::PropertyTagFactory(AtomReflectionProvider* InReflectionProvider)
{
	ReflectionProvider = InReflectionProvider;
	ErrorResult = new PropertyTag(new VoidPointer(*new int(35535)), "ERROR", "ERROR");
}

////////////////////////////////////////////////////////////////
// Factory Methods
PropertyTag PropertyTagFactory::FromSimpleObject(VoidPointer& InObject)
{
	std::string TypeString = '<' + InObject.GetTypeID() + '>';
	std::string ContentString = '[' + ObjectToString(InObject) + ']';
	VoidPointer* Object = new VoidPointer(InObject);
	return PropertyTag(Object, TypeString, ContentString);
}

PropertyTag PropertyTagFactory::FromStream(std::istream& InStream)
{
	/// load complete string
	std::string CompleteString = StreamToString(InStream, '<', '>');

	if (CompleteString == "")
		return *ErrorResult;

	std::stringstream completeStringStream;
	completeStringStream << RemoveStartEndChar(CompleteString);
	/// load type string from complete string
	std::string TypeString = StreamToString(completeStringStream, '<', '>');
	/// load content string from complete string
	std::string ContentString = StreamToString(completeStringStream, '[', ']');

	/// load object from string
	VoidPointer* Object = StringToObject(RemoveStartEndChar(TypeString), RemoveStartEndChar(ContentString));
	return PropertyTag(Object, TypeString, ContentString);
}

////////////////////////////////////////////////////////////////
// Helper Functions
std::string PropertyTagFactory::ObjectToString(const VoidPointer& InPointer)
{
	AtomReflectionInterface* converter = ReflectionProvider->GetReflection(InPointer.GetTypeID());
	return converter->ObjectToString(InPointer);
}

VoidPointer* PropertyTagFactory::StringToObject(const std::string& InType, const std::string& InContent)
{
	AtomReflectionInterface* converter = ReflectionProvider->GetReflection(InType);
	return converter->StringToObject(InContent);
}

std::string PropertyTagFactory::StreamToString(std::istream& InStream, const char& InStringStart, const char& InStringEnd)
{
	std::string result;
	int NumOpenBrackets = 0;

	/// find opening bracket
	while (!InStream.eof())
	{
		if ((InStream.get()) == InStringStart)
		{
			NumOpenBrackets = 1;
			result = InStringStart;
			break;
		}
	}

	while (!InStream.eof() && NumOpenBrackets > 0)
	{
		/// read new character
		char c = InStream.get();
		result.push_back(c);

		if (c == InStringStart)
			NumOpenBrackets++;
		else if (c == InStringEnd)
			NumOpenBrackets--;
	}
	return result;
}

std::vector<std::string> PropertyTagFactory::StringToList(const std::string& InString, const char& InSeperator)
{
	std::vector<std::string> result;

	auto SingleStringBegin = InString.begin();
	for (auto iter = InString.begin(); iter < InString.end(); iter++)
	{
		if (*iter == InSeperator)
		{
			result.push_back(std::string(SingleStringBegin, iter));
			iter++;
			SingleStringBegin = iter;
		}
	}

	if (SingleStringBegin != InString.end())
	{
		result.push_back(std::string(SingleStringBegin, InString.end()));
	}

	return result;
}

std::string PropertyTagFactory::RemoveStartEndChar(const std::string& InString)
{
	return std::string(InString.begin() + 1, InString.end() - 1);
}