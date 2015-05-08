
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Reflection/Element/Public/RClass.h"
using namespace Environment;

RClass::RClass(const std::string &InTypeID, const std::string &InBaseTypeID)
{
	TypeID = InTypeID;
	BaseTypeID = InBaseTypeID;
}

RClass::~RClass()
{

}

std::string RClass::GetType()
{
	return TypeID;
}

bool RClass::IsType(const std::string& InTypeID)
{
	return (InTypeID == TypeID);
}
