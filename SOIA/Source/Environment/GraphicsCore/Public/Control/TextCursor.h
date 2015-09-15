
#pragma once

#include "GeometryObject.h"

namespace Environment
{
	class TextCursor : public GeometryObject
	{
	public:
		TextCursor(MBoundaries* InBoundaries, std::function<std::vector<pxPoint>()> const & InEdges);
		virtual void Update() override;

		int GetPosition();
		void SetPosition(int InPosition);

	private:
		int Position;
		fColor OnColor;
		fColor OffColor;
	};
}