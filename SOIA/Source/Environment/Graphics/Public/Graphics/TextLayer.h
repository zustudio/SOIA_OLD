
#pragma once

#include "GraphicsLayer.h"

#include "TextObject.h"
#include "VertexBufferTemplate.h"
#include "FontTexture2D.h"
#include "fPoint.h"
#include "TextStyle.h"

namespace Environment
{
	class LIBIMPEXP TextLayer : public GraphicsLayer
	{
	public:
		TextLayer(TextStyle const & InStyle);
		virtual void Initialize() override;
		virtual void UpdateBuffers() override;

		virtual void AddObject(GraphicsObject* InObject) override;

		void EraseGraphicsObject(TextObject* InObject);
		void EraseGraphicsObjectFromBuffers(TextObject * InObject);

		FontTexture2D* GetFontTexture();

	private:
		FontTexture2D FontTexture;
		using CommonBufferType = VertexBufferTemplate<float, fPoint::DataUnraveler, fPoint::DataUnraveler>;
		CommonBufferType* VertexBuffer;

		std::vector<TextObject*> TextObjects;
		Vector2D<float> Scale;
	};
}
