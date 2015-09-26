
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
	for (GeometryObject* object : Objects)
	{
		if (object->bUpdateRequested && object->Edges.Get().dim())
		{
			if (object->VertexBufferRange == Range<int>::Empty())
			{
				object->VertexBufferRange.Lower = Vertices.GetEntryNum();
				object->ElementBufferRange.Lower = Lines.GetEntryNum();

				Vertices.AddEmpty(object->Edges.Get().dim());
				Lines.AddEmpty(object->Edges.Get().dim());

				object->VertexBufferRange.Upper = Vertices.GetEntryNum() - 1;
				object->ElementBufferRange.Upper = Lines.GetEntryNum() - 1;
			}

			int index_edge = 0;
			for (int index_vertex : object->VertexBufferRange)
			{
				Vertices.Set(index_vertex, object->CalculateRelativeLocationOnWindow(object->Edges.Get()[index_edge]), object->Color);
				++index_edge;
			}

			int index_vertex = object->VertexBufferRange.Lower;
			int index_line = object->ElementBufferRange.Lower;
			for (index_line; index_line < object->ElementBufferRange.Upper; ++index_line)
			{
				Lines.Set(index_line, iLine(index_vertex, index_vertex + 1));
				++index_vertex;
			}
			Lines.Set(index_line, iLine(index_vertex, object->VertexBufferRange.Lower));
			
			object->bUpdateRequested = false;
		}
	}
}

void UnfilledGeometryLayer::EraseGraphicsObjectFromBuffers(GeometryObject * InObject)
{
	GraphicsLayer::EraseGraphicsObjectFromBuffers(InObject, Objects, &Vertices, &Lines);
}
