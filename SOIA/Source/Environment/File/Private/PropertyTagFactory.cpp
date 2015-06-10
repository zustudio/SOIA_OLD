
#include "Definitions.h"

#include "PropertyTagFactory.h"
using namespace Environment;

#include <sstream>

////////////////////////////////////////////////////////////////
// Initializing
PropertyTagFactory::PropertyTagFactory()
{
	ErrorResult = new PropertyTag(new VoidPointer(*new int(35535)), "ERROR", "ERROR");
}

////////////////////////////////////////////////////////////////
// Factory Methods
PropertyTag PropertyTagFactory::FromObject(const FileObject& InObject)
{
	std::string tags;
	tags += (PropertyTag(nullptr, InObject.Class->GetType(), "").CompleteString);

	for (auto attribute : InObject.Attributes)
	{
		tags += (FromSimpleObject(attribute).CompleteString);
	}

	PropertyTag result = PropertyTag(nullptr, "", "");
	result.CompleteString = tags;
	return result;
}
PropertyTag PropertyTagFactory::FromSimpleObject(VoidPointer& InObject)
{
	std::string ContentString = ObjectToString(InObject);
	VoidPointer* Object = new VoidPointer(InObject);
	return PropertyTag(Object, Object->GetTypeID(), ContentString);
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
	std::string TypeString = RemoveStartEndChar(StreamToString(completeStringStream, '<', '>'));
	/// load content string from complete string
	std::string ContentString = RemoveStartEndChar(StreamToString(completeStringStream, '[', ']'));

	/// load object from string
	VoidPointer* Object = StringToObject(TypeString, ContentString);
	return PropertyTag(Object, TypeString, ContentString);
}

////////////////////////////////////////////////////////////////
// Helper Functions
std::string PropertyTagFactory::ObjectToString(VoidPointer& InPointer)
{
	AtomReflection* converter = GetAtomReflectionProvider()->GetReflection(InPointer.GetTypeID());
	return converter->ObjectToString(InPointer);
}

VoidPointer* PropertyTagFactory::StringToObject(const std::string& InType, const std::string& InContent)
{
	AtomReflection* converter = GetAtomReflectionProvider()->GetReflection(InType);
	if (converter)
		return converter->StringToObject(InContent);
	else
		return nullptr;
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