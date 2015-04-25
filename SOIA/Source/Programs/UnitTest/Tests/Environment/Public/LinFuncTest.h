
// include super class
#include "Programs/UnitTest/Core/Public/TestInterface.h"

// include class to be tested
#include "Environment/Mathematics/Functions/Public/LinearFunction.h"


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
