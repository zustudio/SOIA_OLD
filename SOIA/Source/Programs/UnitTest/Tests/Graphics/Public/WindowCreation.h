
#pragma once

// include super class
#include "TestInterface.h"

// include class to be tested
#include "Window.h"

namespace UnitTest
{
namespace Tests
{
namespace Graphics
{
class WindowCreation : public UnitTest::Core::TestInterface
{
public:
	virtual bool Execute() override;
};
}
}
}
