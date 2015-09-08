
#include "Definitions.h"
#include "OpenGL.h"

#include "UnfilledGeometryLayer.h"
using namespace Environment;

UnfilledGeometryLayer::UnfilledGeometryLayer()
	: GeometryLayer(),
	Lines(VertexBufferType::Elements, BufferContentType::Lines)
{
	this->Configure(
		{ &VertexShader, &FragmentShader },
		{ &Vertices, &Lines },
		VertexBufferType::Elements,
		{},
		"OutColor",
		{ LocationVariable, ColorVariable });
}

void UnfilledGeometryLayer::UpdateBuffers()
{
	for (GeometryObject& object : Objects)
	{
		if (object.bChanged)
		{
			const int IndexOfFirstPoint = Vertices.GetEntryNum();

			for (pxPoint& edge : object.Edges)
			{
				Vertices.Add(object.CalculateRelativeLocationOnWindow(edge), object.Color);
			}

			int IndexOfLastPoint = IndexOfFirstPoint + object.Edges.size() - 1;
			for (int Index = IndexOfFirstPoint; Index < IndexOfLastPoint; ++Index)
			{
				Lines.Add(iLine(Index, Index + 1));
			}
			Lines.Add(iLine(IndexOfFirstPoint, IndexOfLastPoint));
			
			object.bChanged = false;
		}
	}
}
