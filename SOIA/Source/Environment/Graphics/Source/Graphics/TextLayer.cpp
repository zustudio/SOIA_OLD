
#include "Definitions.h"
#include "OpenGL.h"

#include "TextLayer.h"
using namespace Environment;

#include "VertexBufferTemplate.h"
#include "GlobalLogger.h"

#include <algorithm>

TextLayer::TextLayer(TextStyle const & InStyle)
	:
	FontTexture(InStyle)
{
	auto vertexShader = new Shader(ShaderType::Vertex,
		"#version 130\n"
		"in vec2 position;"
		"in vec2 texCoords;"
		"out vec2 TexCoords;"
		"void main()"
		"{"
		"	TexCoords = texCoords;"
		"	gl_Position = vec4(position,0.0,1.0);"
		"}");

	auto fragmentShader = new Shader(ShaderType::Fragment,
		"#version 130\n"
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

void TextLayer::UpdateBuffers()
{
	for (int i = 0; i < TextObjects.size(); ++i)
	{
		TextObject* textObject = TextObjects[i];
		if (textObject->bUpdateRequested)
		{
			bool bVisible = textObject->IsVisible();
			if (!bVisible)
			{
				EraseGraphicsObjectFromBuffers(textObject);
				textObject->VertexBufferRange = Range<int>::Empty();
				continue;
			}
			if (textObject->VertexBufferRange != Range<int>::Empty()
				&& textObject->VertexBufferRange.Count() != textObject->GetText().size() * 6)
			{
				EraseGraphicsObjectFromBuffers(textObject);
				textObject->VertexBufferRange = Range<int>::Empty();
			}
			if (textObject->VertexBufferRange == Range<int>::Empty())
			{
				textObject->VertexBufferRange.Lower = VertexBuffer->GetEntryNum();
				VertexBuffer->AddEmpty(textObject->GetText().size() * 6);
				textObject->VertexBufferRange.Upper = VertexBuffer->GetEntryNum() - 1;
			}

			int CurX = 0;
			int CurY = -FontTexture.GetSpriteSize().Y;

			int index_vertex = textObject->VertexBufferRange.Lower;
			std::string text = textObject->GetText();
			for (char const & character : text)
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
				VertexBuffer->Set(index_vertex++, v_leftTop);
				VertexBuffer->Set(index_vertex++, v_rightTop);
				VertexBuffer->Set(index_vertex++, v_leftBottom);
				//add tri 2
				VertexBuffer->Set(index_vertex++, v_leftBottom);
				VertexBuffer->Set(index_vertex++, v_rightTop);
				VertexBuffer->Set(index_vertex++, v_rightBottom);


				CurX += (glyph.AdvanceX >> 6);
				CurY += (glyph.AdvanceY >> 6);
			}

			textObject->bUpdateRequested = false;
		}
	}
}

void TextLayer::AddObject(GraphicsObject* InObject)
{
	TextObject* object = dynamic_cast<TextObject*>(InObject);
	
	if (!object)
	{
		LOG("Trying to add object, which is not a TextObject to TextLayer.", Logger::Severity::Error);
		return;
	}

	//LOG("Adding textobject '" + object->GetText() + "'.", Logger::Severity::DebugInfo);

	TextObjects.push_back(object);
	InObject->SetDestructorCallback([this](MBound* InObject) {this->EraseGraphicsObject((TextObject*)InObject); });
}

void TextLayer::EraseGraphicsObject(TextObject * InObject)
{
	//LOG("Erasing textobject '" + InObject->GetText() + "'.", Logger::Severity::DebugInfo);

	EraseGraphicsObjectFromBuffers(InObject);
	auto iter_object = std::find(TextObjects.begin(), TextObjects.end(), InObject);
	if (iter_object != TextObjects.end())
		TextObjects.erase(iter_object);
}

void TextLayer::EraseGraphicsObjectFromBuffers(TextObject * InObject)
{
	GraphicsLayer::EraseGraphicsObjectFromBuffers(InObject, TextObjects, VertexBuffer, nullptr);
}

FontTexture2D * TextLayer::GetFontTexture()
{
	return &FontTexture;
}
