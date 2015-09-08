
#include "Definitions.h"
#include "OpenGL.h"

#include "FilledGeometryLayer.h"
using namespace Environment;

FilledGeometryLayer::FilledGeometryLayer()
	: Triangles(VertexBufferType::Elements, BufferContentType::Triangles)
{
	this->Configure(
		{ &VertexShader, &FragmentShader },
		{ &Vertices, &Triangles},
		VertexBufferType::Elements,
		{},
		"OutColor",
		{ LocationVariable, ColorVariable });
}

void FilledGeometryLayer::UpdateBuffers()
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
			for (int Index = IndexOfFirstPoint + 1; Index < IndexOfLastPoint - 1; Index+=2)
			{
				Triangles.Add(iTriangle(IndexOfFirstPoint, Index, Index + 1));
			}
			Triangles.Add(iTriangle(IndexOfFirstPoint, IndexOfLastPoint - 1, IndexOfLastPoint));

			object.bChanged = false;
		}
	}
}
