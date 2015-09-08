
#include "Definitions.h"
#include "OpenGL.h"

#include "TextLayer.h"
using namespace Environment;

#include "VertexBufferTemplate.h"

TextLayer::TextLayer(Font const & InFont, int InSize)
	:
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


void TextLayer::Initialize()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GraphicsLayer::Initialize();
}

void TextLayer::Draw()
{
	//auto Scale = PixelSize->Convert<float>().Divide1() * 2;

	VertexBuffer->BackBuffer.clear();
	for (auto textObject : TextObjects)
	{
		int CurX = 0;
		int CurY = -FontTexture.GetSpriteSize().Y;

		for (char& character: textObject->Text)
		{
			CheckGLError();
			GlyphObject& glyph = FontTexture.GetGlyph(character);


			int x2 = CurX + glyph.BitmapLeft;
			int y2 = -CurY - glyph.BitmapTop;
			int w = glyph.Width;
			int h = glyph.Rows;


			fPoint leftTop, rightBottom;
			fPoint rightTop, leftBottom;
			FontTexture.GetCoordinates(character, leftTop, rightBottom);
			rightTop = fPoint(rightBottom.X, leftTop.Y);
			leftBottom = fPoint(leftTop.X, rightBottom.Y);

			using TT = CommonBufferType::TupleType;
			TT v_leftTop = TT(textObject->CalculateRelativeLocationOnWindow(pxPoint(x2, y2)), leftTop);
			TT v_rightTop = TT(textObject->CalculateRelativeLocationOnWindow(pxPoint(x2 + w, y2)), rightTop);
			TT v_leftBottom = TT(textObject->CalculateRelativeLocationOnWindow(pxPoint(x2, y2 + h)), leftBottom);
			TT v_rightBottom = TT(textObject->CalculateRelativeLocationOnWindow(pxPoint(x2 + w, y2 + h)), rightBottom);

			//add tri 1
			VertexBuffer->Add(v_leftTop);
			VertexBuffer->Add(v_rightTop);
			VertexBuffer->Add(v_leftBottom);
			//add tri 2
			VertexBuffer->Add(v_leftBottom);
			VertexBuffer->Add(v_rightTop);
			VertexBuffer->Add(v_rightBottom);


			CurX += (glyph.AdvanceX >> 6);
			CurY += (glyph.AdvanceY >> 6);
		}
	}

	// Main Call
	GraphicsLayer::Draw();
}

void TextLayer::AddTextObject(TextObject * InObject)
{
	TextObjects.push_back(InObject);
}