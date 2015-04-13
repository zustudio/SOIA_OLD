#pragma once

namespace Graphics
{
	class DLLIMPEXP fColor
	{
	public:
		fColor();
		fColor(float NewR, float NewG, float NewB, float NewA = 1);
		~fColor();

		float R, G, B, A;

		void Set(float NewR, float NewG, float NewB, float NewA = 1);

	};
}
