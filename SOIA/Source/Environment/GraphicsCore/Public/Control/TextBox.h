
#pragma once

#include "GraphicsControl.h"

namespace Environment
{
	class LIBIMPEXP TextBox : public GraphicsControl
	{
	public:
		TextBox(MBoundaries* InBoundaries, pxMargins InMargins);

		void SetText(std::string const & InText);

		std::string Text;

	private:
		
	};
}
