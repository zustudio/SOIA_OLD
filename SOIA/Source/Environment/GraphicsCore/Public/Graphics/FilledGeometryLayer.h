
#pragma once

#include "GeometryLayer.h"

#include "iTriangle.h"

namespace Environment
{
	class FilledGeometryLayer : public GeometryLayer
	{
	public:
		FilledGeometryLayer();

		virtual void UpdateBuffers() override;

	private:
		VertexBufferTemplate<int, iTriangle::DataUnraveler> Triangles;
	};
}