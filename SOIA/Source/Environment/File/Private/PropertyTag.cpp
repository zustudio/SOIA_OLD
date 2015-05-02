
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/File/Public/PropertyTag.h"
using namespace Environment;

PropertyTag::PropertyTag(VoidPointer* InObject, const std::string& InTypeString, const std::string& InContentString)
	: Object(InObject),
	TypeString(InTypeString),
	ContentString(InContentString),
	CompleteString("<<" + InTypeString + ">[" + InContentString + "]>")
{}