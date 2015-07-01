#include "UnitTest++/UnitTest++.h"
#include "LibImpExpMacros.generated.h"
#include "RElement.h"
using namespace Environment;

RCLASS(RTest,RElement)
class RTest : public RTest_Base
{
	RCLASS_BEGIN()

	RTest();

	RPROPERTY(prop_int)
		int prop_int;

	RCLASS_END()
};

RTest::RTest()
	: RTest_Base(),
	prop_int(1)
{
	ReflectAttributes();
}

TEST(AttributeMirror)
{
	GetAtomReflectionProvider()->Reflect<int>();

	auto testobject = RTest();

	auto vp_prop_int = testobject.GetAttribute("prop_int");
	auto prop_int = vp_prop_int.CastAndDereference<int>();
	CHECK_EQUAL(1, 1);

	VoidPointer i = VoidPointer(new int(4));
}