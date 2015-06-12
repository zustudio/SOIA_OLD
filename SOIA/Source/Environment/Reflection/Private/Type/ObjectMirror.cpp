
#include "Definitions.h"

#include "ObjectMirror.h"
using namespace Environment;

ObjectMirror::ObjectMirror(const std::string& InName)
	:
	Name(InName)
{}

std::string& ObjectMirror::GetName()
{
	return Name;
}