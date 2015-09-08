
#pragma once

#include "GraphicsLayer.h"

#include "VertexBufferTemplate.h"
#include "fPoint.h"
#include "fColor.h"
#include "GeometryObject.h"

namespace Environment
{
	class GeometryLayer : public GraphicsLayer
	{
	public:
		GeometryLayer();

		void AddObject(GeometryObject const & InObject);

	protected:
		VertexBufferTemplate<float, fPoint::DataUnraveler, fColor::DataUnraveler>  Vertices;
		VertexBufferVariable LocationVariable;
		VertexBufferVariable ColorVariable;
		Shader VertexShader;
		Shader FragmentShader;

		std::vector<GeometryObject> Objects;
	};
}