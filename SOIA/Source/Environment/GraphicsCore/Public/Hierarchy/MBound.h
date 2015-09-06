
#pragma once

namespace Environment
{
	class MBoundaries;
}

namespace Environment
{
	class MBound
	{

	public:
		void SetBoundaries(MBoundaries* InBoundaries);

	private:
		MBoundaries* Boundaries;
	};
}