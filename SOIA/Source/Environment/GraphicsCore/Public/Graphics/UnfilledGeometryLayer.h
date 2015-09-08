
#pragma once

#include "GeometryLayer.h"

#include "iLine.h"

namespace Environment
{
	class UnfilledGeometryLayer : public GeometryLayer
	{
	public:
		UnfilledGeometryLayer();

		virtual void UpdateBuffers() override;

	private:
		VertexBufferTemplate<int, iLine::DataUnraveler> Lines;
	};
}