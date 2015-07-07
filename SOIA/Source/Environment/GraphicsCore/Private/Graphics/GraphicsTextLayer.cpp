
#include "Definitions.h"
#include "OpenGL.h"

#include "GraphicsTextLayer.h"
using namespace Environment;

#include "CommonDataUnravelers.h"
#include "VertexBufferTemplate.h"

Environment::GraphicsTextLayer::GraphicsTextLayer(const std::vector<TextObject*>& InTextObjects)
	:
	TextObjects(InTextObjects)
{
	auto vertexShader = new Shader(ShaderType::Vertex,
		"#version 400\n"
		"in vec2 position;"
		"in vec2 texCoords;"
		"out vec2 TexCoords;"
		"void main()"
		"{"
		"	TexCoords = texCoords;"
		"	gl_Position = vec4(position,0.0,1.0);"
		"}");

	auto fragmentShader = new Shader(ShaderType::Fragment,
		"#version 400\n"
		"in vec2 TexCoords;"
		"uniform sampler2D sampler;"
		"out vec4 outColor;"
		"void main()"
		"{"
		"	outColor = vec4(1, 1, 1, texture(sampler, TexCoords).r) * vec4(0.5, 0, 0, 1);"
		"}");

	CommonBuffer = new CommonBufferType(VertexBufferType::Vertices, BufferContentType::TriangleStrip);
	auto positionVar = CommonBuffer->CreateVariable(0, "position");
	auto texCoordsVar = CommonBuffer->CreateVariable(1, "texCoords");

	CommonTexture = new Texture2D(nullptr, 0, 0, TextureChannels::R);

	this->Configure
	(
		{ vertexShader, fragmentShader },
		{ CommonBuffer },
		VertexBufferType::Vertices,
		{ CommonTexture },
		"outColor",
		{positionVar, texCoordsVar}
	);
}

void GraphicsTextLayer::Initialize(Vector2D<int>* InSize)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (auto textObj : TextObjects)
	{
		textObj->Initialize();
	}
	CheckGLError();

	GraphicsLayer::Initialize(InSize);
}

void GraphicsTextLayer::Draw()
{
	auto Scale = PixelSize->Convert<float>().Divide1() * 2;
	for (auto textObject : TextObjects)
	{
		float CurX = textObject->Position.X;
		float CurY = textObject->Position.Y;

		for (auto glyph : textObject->Glyphs)
		{
			*CommonTexture = glyph->Texture;
			CheckGLError();

			float x2 = CurX + glyph->BitmapLeft * Scale.X;
			float y2 = -CurY - glyph->BitmapTop * Scale.Y;
			float w = glyph->Width * Scale.X;
			float h = glyph->Rows * Scale.Y;

			using TT = CommonBufferType::TupleType;
			CommonBuffer->BackBuffer = std::vector<TT>(
			{
				TT(Vector2D<float>(x2, -y2), Vector2D<float>(0,0)),
				TT(Vector2D<float>(x2 + w, -y2), Vector2D<float>(1,0)),
				TT(Vector2D<float>(x2, -y2 -h), Vector2D<float>(0,1)),
				TT(Vector2D<float>(x2 + w, -y2 -h), Vector2D<float>(1,1)),
			});
			CommonBuffer->RequestBufferUpdate();

			// Main Call
			GraphicsLayer::Draw();

			CurX += (glyph->AdvanceX >> 6) * Scale.X;
			CurY += (glyph->AdvanceY >> 6) * Scale.Y;
		}
	}
}