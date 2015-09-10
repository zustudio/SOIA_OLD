
#pragma once

#include "DataUnravelerTemplate.h"

namespace Environment
{
	class iTriangle
	{
	public:
		iTriangle();
		iTriangle(int ina, int inb, int inc);

		int A;
		int B;
		int C;

		using DataUnraveler = DataUnravelerTemplate<iTriangle, int, &iTriangle::A, &iTriangle::B, &iTriangle::C>;
	};
}
