#include "UnitTest++.h"
#include "LibImpExpMacros.generated.h"
#include "VoidPointer.h"
using namespace Environment;

TEST(SmartPointer_Deleting)
{
	int* rawpointer;
	{
		VoidPointer p_int = VoidPointer::Nullpointer();
		{
			rawpointer = new int(1);
			p_int = VoidPointer(rawpointer);

			{
				VoidPointer p_int2 = p_int;
				int test = p_int2.CastAndDereference<int>();
				CHECK_EQUAL(1, test);
			}
		}
		int test = p_int.CastAndDereference<int>();
		CHECK_EQUAL(1, test);
	}
	/*int out_of_scope = *rawpointer;
	CHECK_EQUAL(true, out_of_scope != 1);*/
}

TEST(SmartPointer_Stack)
{
	{
		int a = 1;
		VoidPointer p_a = VoidPointer(&a, EMemoryType::Stack);
	}
}
