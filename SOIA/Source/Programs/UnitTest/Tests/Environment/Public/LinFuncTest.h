
// include super class
#include "TestInterface.h"

// include class to be tested
#include "LinearFunction.h"


namespace UnitTest
{
namespace Tests
{
namespace Environment
{
	class LinFuncTest : public UnitTest::Core::TestInterface
	{
	public:
		virtual bool Execute() override;
	};
}
}
}
