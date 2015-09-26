
#include "Definitions.h"

#include "RConversionPipes.h"
using namespace Supervisor;

RConversionPipes::RConversionPipes()
	:
	BaseType()
{
	ReflectAttributes();
}

bool RConversionPipes::pipe_1DoubleTo2Double(const double & In, double & Out1, double & Out2)
{
	Out1 = In;
	Out2 = In;
	return true;
}

bool RConversionPipes::pipe_IntToString(const int & In, std::string & Out)
{
	Out = std::to_string(In);
	return true;
}
