#include "UnitTest++/UnitTestPP.h"

TEST(SomeTest)
{
    CHECK_EQUAL(1,1);
}

int main(int, char const *[])
{
    return UnitTest::RunAllTests();
}
