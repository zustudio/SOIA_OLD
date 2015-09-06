
#pragma once

#include "GraphicsLayer.h"

#include "TextObject.h"
#include "VertexBufferTemplate.h"
#include "FontTexture2D.h"
#include "fPoint.h"

namespace Environment
{
	class LIBIMPEXP TextLayer : public GraphicsLayer
	{
	public:
		TextLayer(Font const & InFont, int InSize, const std::vector<TextObject*>& InTextObjects);
		virtual void Initialize(Vector2D<int>* InSize) override;
		virtual void Draw() override;

		FontTexture2D FontTexture;
		using CommonBufferType = VertexBufferTemplate<float, fPoint::DataUnraveler, fPoint::DataUnraveler>;
		CommonBufferType* VertexBuffer;

		std::vector<TextObject*> TextObjects;
		Vector2D<float> Scale;
	};
}