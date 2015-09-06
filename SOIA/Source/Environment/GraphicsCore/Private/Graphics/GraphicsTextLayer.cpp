
#include "Definitions.h"
#include "OpenGL.h"

#include "GraphicsTextLayer.h"
using namespace Environment;

#include "VertexBufferTemplate.h"

GraphicsTextLayer::GraphicsTextLayer(Font const & InFont, int InSize, const std::vector<TextObject*>& InTextObjects)
	:
	TextObjects(InTextObjects),
	FontTexture(InFont, InSize)
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
		"	outColor = vec4(1, 1, 1, texture(sampler, TexCoords).r) * vec4(0, 0, 0, 1);"
		"}");

	VertexBuffer = new CommonBufferType(VertexBufferType::Vertices, BufferContentType::Triangles);
	auto positionVar = VertexBuffer->CreateVariable(0, "position");
	auto texCoordsVar = VertexBuffer->CreateVariable(1, "texCoords");

	this->Configure
	(
		{ vertexShader, fragmentShader },
		{ VertexBuffer },
		VertexBufferType::Vertices,
		{ &FontTexture },
		"outColor",
		{positionVar, texCoordsVar}
	);
}


void GraphicsTextLayer::Initialize(Vector2D<int>* InSize)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//for (auto textObj : TextObjects)
	//{
	//	textObj->Initialize();
	//}
	//CheckGLError();

	GraphicsLayer::Initialize(InSize);
}

void GraphicsTextLayer::Draw()
{
	auto Scale = PixelSize->Convert<float>().Divide1() * 2;

	VertexBuffer->BackBuffer.clear();
	for (auto textObject : TextObjects)
	{
		float CurX = textObject->Position.X;
		float CurY = textObject->Position.Y;

		for (char& character: textObject->Text)
		{
			CheckGLError();
			GlyphObject& glyph = FontTexture.GetGlyph(character);


			float x2 = CurX + glyph.BitmapLeft * Scale.X;
			float y2 = -CurY - glyph.BitmapTop * Scale.Y;
			float w = glyph.Width * Scale.X;
			float h = glyph.Rows * Scale.Y;


			fPoint leftTop, rightBottom;
			fPoint rightTop, leftBottom;
			FontTexture.GetCoordinates(character, leftTop, rightBottom);
			rightTop = fPoint(rightBottom.X, leftTop.Y);
			leftBottom = fPoint(leftTop.X, rightBottom.Y);

			using TT = CommonBufferType::TupleType;
			TT v_leftTop = TT(fPoint(x2, -y2), leftTop);
			TT v_rightTop = TT(fPoint(x2 + w, -y2), rightTop);
			TT v_leftBottom = TT(fPoint(x2, -y2 -h), leftBottom);
			TT v_rightBottom = TT(fPoint(x2 + w, -y2 -h), rightBottom);

			//add tri 1
			VertexBuffer->Add(v_leftTop);
			VertexBuffer->Add(v_rightTop);
			VertexBuffer->Add(v_leftBottom);
			//add tri 2
			VertexBuffer->Add(v_leftBottom);
			VertexBuffer->Add(v_rightTop);
			VertexBuffer->Add(v_rightBottom);


			CurX += (glyph.AdvanceX >> 6) * Scale.X;
			CurY += (glyph.AdvanceY >> 6) * Scale.Y;
		}
	}

	// Main Call
	GraphicsLayer::Draw();
}