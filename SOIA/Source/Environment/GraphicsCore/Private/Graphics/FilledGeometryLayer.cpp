
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
	for (GeometryObject* object : Objects)
	{
		if (object->bUpdateRequested)
		{
			if (object->VertexBufferRange == Range<int>::Empty())
			{
				object->VertexBufferRange.Lower = Vertices.GetEntryNum();
				object->ElementBufferRange.Lower = Triangles.GetEntryNum();

				int edges = object->Edges.size();
				Vertices.AddEmpty(edges);
				Triangles.AddEmpty(edges - 2);

				object->VertexBufferRange.Upper = Vertices.GetEntryNum() - 1;
				object->ElementBufferRange.Upper = Triangles.GetEntryNum() - 1;
			}

			int index_edge = 0;
			for (int index_vertex : object->VertexBufferRange)
			{
				Vertices.Set(index_vertex, object->CalculateRelativeLocationOnWindow(object->Edges[index_edge]), object->Color);
				++index_edge;
			}

			int index_vertex_zero = object->VertexBufferRange.Lower;
			int index_vertex = index_vertex_zero + 1;
			for (int index_triangle : object->ElementBufferRange)
			{
				Triangles.Set(index_triangle, iTriangle(index_vertex_zero, index_vertex, index_vertex + 1));
				++index_vertex;
			}

			object->bUpdateRequested = false;
		}
	}
}

void FilledGeometryLayer::EraseGraphicsObjectFromBuffers(GeometryObject * InObject)
{
	GraphicsLayer::EraseGraphicsObjectFromBuffers(InObject, Objects, &Vertices, &Triangles);
}