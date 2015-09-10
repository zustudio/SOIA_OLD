
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
		TextLayer(Font const & InFont, int InSize);
		virtual void Initialize() override;
		virtual void UpdateBuffers() override;

		void AddTextObject(TextObject* InObject);

		FontTexture2D FontTexture;
		using CommonBufferType = VertexBufferTemplate<float, fPoint::DataUnraveler, fPoint::DataUnraveler>;
		CommonBufferType* VertexBuffer;

		std::vector<TextObject*> TextObjects;
		Vector2D<float> Scale;
	};
}
