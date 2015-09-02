#include "UnitTest++/UnitTest++.h"

#include "MathContainer.h"

TEST(ParseSimpleMathematics)
{
	MathContainer mathContainer;
	auto function = mathContainer.ParseString("2*3+4-5/7");
	CHECK(function);

	double result = function->Execute({});
	CHECK_EQUAL(10.0-5.0/7.0, result);
}

TEST(ParseParenthesis)
{
	MathContainer mathContainer;
	auto function = mathContainer.ParseString("2*(3+4-5)/7");
	CHECK(function);

	double result = function->Execute({});
	CHECK_EQUAL(4.0 / 7.0, result);
}

TEST(ParseVariableDefinition)
{
	MathContainer mathContainer;
	mathContainer.ParseString("myVar=40");
	double result = mathContainer.ParseString("myVar+2")->Execute({});
	CHECK_EQUAL(42, result);

	double undefined = mathContainer.ParseString("undefined")->Execute({});
	CHECK_EQUAL(0, undefined);
}

TEST(ParseFunctionDefinition)
{
	MathContainer mathContainer;
	mathContainer.ParseString("f(x)=2*x");
	double result = mathContainer.ParseString("f(3)")->Execute({});
	CHECK_EQUAL(6, result);
}