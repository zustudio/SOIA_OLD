
#pragma once

#include "Programs/UnitTest/Core/Public/TestInterface.h"

namespace UnitTest
{
	class MathTest : public Core::TestInterface
	{
	public:
		virtual bool Execute() override;
	};
}