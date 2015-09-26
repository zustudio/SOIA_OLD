
#pragma once

#include "GeometryLayer.h"

#include "iLine.h"

namespace Environment
{
	class LIBIMPEXP UnfilledGeometryLayer : public GeometryLayer
	{
	public:
		UnfilledGeometryLayer();

		virtual void UpdateBuffers() override;

	private:
		virtual void EraseGraphicsObjectFromBuffers(GeometryObject* InObject) override;

	private:
		VertexBufferTemplate<int, iLine::DataUnraveler> Lines;
	};
}