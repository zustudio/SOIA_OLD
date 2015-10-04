
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

		void SetSize(float InSize);
		void SetOffset(float InOffset);

	private:
		void UpdateEdges();

	private:
		float Size;
		float Offset;
	};
}