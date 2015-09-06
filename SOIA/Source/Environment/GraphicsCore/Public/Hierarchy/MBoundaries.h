
#pragma once

#include "MBound.h"

namespace Environment
{
	class MBoundaries : MBound
	{
		friend MBound;

	protected:
		void AddBoundObject(MBound* InBoundObject);

	private:
		std::vector<MBound*> BoundObjects;
	};
}