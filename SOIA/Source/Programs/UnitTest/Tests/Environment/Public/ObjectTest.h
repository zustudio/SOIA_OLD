
#pragma once

#include "Programs/UnitTest/Core/Public/TestInterface.h"

#define DLLIMPEXP
#include "Environment/Reflection/ID/Public/RFunction.h"
#include "Environment/Reflection/ID/Public/RElement.h"

namespace UnitTest
{
	class ObjectTest : public Core::TestInterface, public Environment::RElement
	{
	public:
		ObjectTest();
		virtual bool Execute() override;
		
		Environment::RFunction<ObjectTest>* MyFuncObject;
		Environment::RFunction<ObjectTest>::TargetFunctionType MyFunc;
		
	};
}