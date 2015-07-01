
#pragma once

namespace Environment
{
	class RContainer;
	class LIBIMPEXP ResolveInfoInterface
	{
	public:
		virtual void OverrideContainer(RContainer*) = 0;
	};
}