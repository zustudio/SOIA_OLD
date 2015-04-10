
#pragma once

namespace UnitTest
{
namespace Core
{
class TestInterface
{
public:
	/////////////////////////////////////////////////////////
	// Execution

	/** Executes this test.
	 *  Return depends on whether this test was successfull.
	 *  @return True, if test was sucessfull.
	 */
	virtual bool Execute() = 0;
};
}
}
