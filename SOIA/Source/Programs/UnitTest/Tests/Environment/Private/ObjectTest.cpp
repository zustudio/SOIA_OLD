
#include "Programs/UnitTest/Core/Classes/PrivateDefinitions.h"

#include "Programs/UnitTest/Tests/Environment/Public/ObjectTest.h"
#include "Environment/Reflection/Element/Public/RContainer.h"

#include <iostream>

using namespace UnitTest;


using namespace Environment;

ObjectTest::ObjectTest()
{
	MyFuncObject = new FunctionObject<ObjectTest>(this, &ObjectTest::MyFunc);
}

bool ObjectTest::Execute()
{
	MyFuncObject->Execute(RElement(), {});
	
	return true;
}

bool ObjectTest::MyFunc(const RElement& InCaller, const std::vector<SO::Base::VoidPointer> &InArgs)
{
	std::cout << "Worked!!!!" << std::endl;
	return true;
}