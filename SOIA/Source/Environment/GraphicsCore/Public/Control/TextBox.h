
#pragma once

#include "GraphicsControl.h"

#include "TextObject.h"

namespace Environment
{
	class LIBIMPEXP TextBox : public GraphicsControl
	{
	public:
		TextBox(MBoundaries* InBoundaries, pxMargins InMargins);

		virtual void Update() override;

		void SetText(std::string const & InText);


	private:
		std::string Text;
		std::vector<TextObject> TextObjects;
		
	};
}
