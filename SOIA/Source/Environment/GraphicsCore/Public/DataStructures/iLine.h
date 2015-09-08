
#pragma once

#include "DataUnravelerTemplate.h"

namespace Environment
{
	class iLine
	{
	public:
		iLine(int InA, int InB);

		int A;
		int B;

		using DataUnraveler = DataUnravelerTemplate<iLine, int, &iLine::A, &iLine::B>;
	};
}