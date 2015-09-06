
#pragma once

#include "DataUnravelerTemplate.h"

namespace Environment
{
	class LIBIMPEXP fColor
	{
	public:
		fColor();
		fColor(float NewR, float NewG, float NewB, float NewA = 1);
		~fColor();

		void Set(float NewR, float NewG, float NewB, float NewA = 1);

		float R, G, B, A;

		using DataUnraveler = DataUnravelerTemplate<fColor, float, &fColor::R, &fColor::G, &fColor::B, &fColor::A>;
	};
}
