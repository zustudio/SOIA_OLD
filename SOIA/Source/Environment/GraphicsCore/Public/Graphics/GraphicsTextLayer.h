
#pragma once

#include "GraphicsLayer.h"

#include "TextObject.h"
#include "VertexBufferTemplate.h"
#include "CommonDataUnravelers.h"

namespace Environment
{
	class LIBIMPEXP GraphicsTextLayer : public GraphicsLayer
	{
	public:
		GraphicsTextLayer(const std::vector<TextObject*>& InTextObjects);
		virtual void Initialize(Vector2D<int>* InSize) override;
		virtual void Draw() override;


		Texture2D* CommonTexture;
		using CommonBufferType = VertexBufferTemplate<float, Vector2DFloatUnraveler, Vector2DFloatUnraveler>;
		CommonBufferType* CommonBuffer;
		std::vector<TextObject*> TextObjects;
		Vector2D<float> Scale;
	};
}