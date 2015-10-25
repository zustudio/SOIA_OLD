#include "UnitTest++.h"
#include "LibImpExpMacros.generated.h"
#include "RElement.h"
using namespace Environment;

RCLASS(RTest,RElement)
class RTest : public RTest_Base
{
	RCLASS_BEGIN()

	RTest();

public:
	RPROPERTY(prop_int)
		int prop_int;

protected:
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

	ObjectMirror* attributeMirror = obj.GetAttribute("prop_int");
	auto prop_int = attributeMirror->Object().CastAndDereference<int>();
	CHECK_EQUAL(1, prop_int);

	attributeMirror = obj.GetAttribute("prop_string");
	auto prop_string = attributeMirror->Object().CastAndDereference<std::string>();
	CHECK_EQUAL("test string", prop_string);

}

TEST(SetAttributeMirror)
{
	RTest obj = RTest();

	ObjectMirror* attributeMirror = obj.GetAttribute("prop_int");
	int& prop_int = attributeMirror->Object().CastAndDereference<int>();
	prop_int = 2;

	CHECK_EQUAL(2, obj.prop_int);
}
