
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

		virtual void AddObject(GraphicsObject* InObject) override;

	protected:
		void EraseGraphicsObject(GeometryObject * InObject);
		virtual void EraseGraphicsObjectFromBuffers(GeometryObject * InObject) = 0;

	protected:
		VertexBufferTemplate<float, fPoint::DataUnraveler, fColor::DataUnraveler>  Vertices;
		VertexBufferVariable LocationVariable;
		VertexBufferVariable ColorVariable;
		Shader VertexShader;
		Shader FragmentShader;

		std::vector<GeometryObject*> Objects;
	};
}