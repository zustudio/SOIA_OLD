
#include "Definitions.h"

#include "RElementBase.h"
using namespace Environment;

#include "ReflectionProviders.h"

std::vector<Environment::MemberMirror*> RElementBase::Internal_MemberMirrors = {};

void RElementBase::Internal_GetMemberMirrors(std::vector<MemberMirror*>& InMemberMirrors)
{
}

RClass* RElementBase::GetClass()
{
	return GetElementReflectionProvider()->GetClass(TypeID::FromType<RElement>());
}

RClass* RElementBase::StaticClass()
{
	return GetElementReflectionProvider()->GetClass(TypeID::FromType<RElement>());
}