
#pragma once

#include "GeometryObject.h"

namespace Environment
{
	class LIBIMPEXP TextCursor : public GeometryObject
	{
	public:
		TextCursor(MBoundaries* InBoundaries, std::function<std::vector<pxPoint>()> const & InEdges);
		virtual void Update() override;

		void SetVisibility(bool Visible);
		int GetPosition();
		void SetPosition(int InPosition);

	private:
		int Position;
		fColor OnColor;
		fColor OffColor;
		bool bVisible;
	};
}