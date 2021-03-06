#include "UnitTest++.h"

#include "Range.h"
using namespace Environment;

TEST(RangedForLoop)
{
	Range<int> range = Range<int>(0, 5);

	int sum = 0;
	for (int i : range)
	{
		sum += i;
	}
	CHECK_EQUAL(0 + 1 + 2 + 3 + 4 + 5, sum);
}

TEST(IntegerCount)
{
	Range<int> range = Range<int>(0, 3);

	CHECK_EQUAL(4, range.Count());
}
