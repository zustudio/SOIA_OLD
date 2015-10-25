#include "UnitTest++.h"

#include "MathContainer.h"
using namespace Environment;

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

TEST(ParseRecursiveFunction)
{
	MathContainer mathContainer;
	mathContainer.ParseString("fact(x)=x*fact(x-1)");
	mathContainer.ParseString("fact(0)=1");
	double result = mathContainer.ParseString("fact(4)")->Execute({});
	CHECK_EQUAL(24, result);

	mathContainer.ParseString("fibo(n)=fibo(n-1)+fibo(n-2)");
	mathContainer.ParseString("fibo(0)=0");
	mathContainer.ParseString("fibo(1)=1");
	double fibo10 = mathContainer.ParseString("fibo(10)")->Execute({});
	CHECK_EQUAL(55, fibo10);
}
