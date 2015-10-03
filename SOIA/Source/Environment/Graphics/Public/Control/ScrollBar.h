
#pragma once

#include "GeometryObject.h"

namespace Environment
{
	enum class EScrollBarConfiguration
	{
		Vertical,
		Horizontal
	};

	class LIBIMPEXP ScrollBar : public GeometryObject
	{
	public:
		ScrollBar(MBoundaries* InBoundaries, EScrollBarConfiguration InConfiguration);

		void Set(float InSize, float InOffset);

	};
}