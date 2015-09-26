
#include "Definitions.h"

#include "RElementBase.h"
using namespace Environment;

#include "RElement.h"
#include "GlobalReflectionProviders.h"

std::vector<Environment::MemberMirror*> RElementBase::INTERNAL_NAME(MemberMirrors) = {};

void RElementBase::INTERNAL_NAME(GetMemberMirrors)(std::vector<MemberMirror*>& InMemberMirrors)
{}

RClass* RElementBase::GetClass()
{
	return GlobalRClassProvider()->GetClass(TypeID::FromType<RElement>());
}

RClass* RElementBase::StaticClass()
{
	return GlobalRClassProvider()->GetClass(TypeID::FromType<RElement>());
}