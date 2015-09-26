
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

		fColor operator+(fColor const & InOther) const
		{
			return fColor(R + InOther.R, G + InOther.G, B + InOther.B, A + InOther.A);
		}

		fColor operator-(fColor const & InOther) const
		{
			return fColor(R - InOther.R, G - InOther.G, B - InOther.B, A - InOther.A);
		}

		fColor operator*(float f) const
		{
			return fColor(R * f, G * f, B * f, A * f);
		}

		bool operator==(fColor const & InOther) const
		{
			return R == InOther.R
				&& G == InOther.G
				&& B == InOther.B
				&& A == InOther.A;
		}

		float R, G, B, A;

		using DataUnraveler = DataUnravelerTemplate<fColor, float, &fColor::R, &fColor::G, &fColor::B, &fColor::A>;
	};
}
