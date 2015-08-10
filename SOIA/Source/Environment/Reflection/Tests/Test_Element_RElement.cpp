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

	RPROPERTY(prop_string)
		std::string prop_string;

	RCLASS_END()
};

RTest::RTest()
	: RTest_Base(),
	prop_int(1),
	prop_string("test string")
{
	ReflectAttributes();
}

TEST(GetAttributeMirror)
{
	RTest obj = RTest();
	RTest obj2 = RTest();

	ObjectMirror* attributeMirror = obj.GetAttribute("prop_int");
	auto prop_int = attributeMirror->Object().CastAndDereference<int>();
	CHECK_EQUAL(1, prop_int);
}

TEST(SetAttributeMirror)
{
	RTest obj = RTest();

	ObjectMirror* attributeMirror = obj.GetAttribute("prop_int");
	int& prop_int = attributeMirror->Object().CastAndDereference<int>();
	prop_int = 2;

	CHECK_EQUAL(2, obj.prop_int);
}