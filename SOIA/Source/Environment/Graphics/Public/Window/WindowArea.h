
#pragma once

#include "RenderTarget.h"
#include "GeometryObject.h"

namespace Environment
{
	class LIBIMPEXP WindowArea : public RenderTarget
	{
	public:
		WindowArea(MBoundaries* InBoundaries, pxMargins InMargins, StyleSheet InStyle);

		virtual void Draw() override;

	protected:
		GeometryObject Background;
	};
}