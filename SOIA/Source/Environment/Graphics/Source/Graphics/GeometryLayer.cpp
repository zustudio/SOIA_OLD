
#include "Definitions.h"
#include "OpenGL.h"

#include "GeometryLayer.h"
using namespace Environment;

#include "GlobalLogger.h"

#include <algorithm>

GeometryLayer::GeometryLayer()
	: GraphicsLayer(),

	Vertices(VertexBufferType::Vertices, BufferContentType::Points),

	LocationVariable(Vertices.CreateVariable(0, "InLocation")),
	ColorVariable(Vertices.CreateVariable(1, "InColor")),

	VertexShader(ShaderType::Vertex,
		"#version 400\n"
		"in vec2 InLocation;"
		"in vec4 InColor;"
		"out vec4 VertColor;"
		"void main()"
		"{"
		"	VertColor = InColor;"
		"	gl_Position = vec4(InLocation,0.0,1.0);"
		"}"),
	FragmentShader(ShaderType::Fragment,
		"#version 400\n"
		"in vec4 VertColor;"
		"out vec4 OutColor;"
		"void main()"
		"{"
		"	OutColor = VertColor;"
		"}")
{}

void GeometryLayer::AddObject(GraphicsObject* InObject)
{
	GeometryObject* object = dynamic_cast<GeometryObject*>(InObject);

	if (!object)
	{
		LOG("Trying to add object, which is not a GeometryObject to a GeometryLayer.", Logger::Severity::Error);
		return;
	}

	Objects.push_back(object);
	InObject->SetDestructorCallback([this](MBound* InObject) { EraseGraphicsObject((GeometryObject*)InObject); });
}

void GeometryLayer::EraseGraphicsObject(GeometryObject * InObject)
{
	EraseGraphicsObjectFromBuffers(InObject);

	auto iter_object = std::find(Objects.begin(), Objects.end(), InObject);
	if (iter_object != Objects.end())
		Objects.erase(iter_object);
}
