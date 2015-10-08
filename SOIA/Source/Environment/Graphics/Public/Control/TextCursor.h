
#pragma once

#include "GeometryObject.h"

#include <chrono>

namespace Environment
{
	class LIBIMPEXP TextCursor : public GeometryObject
	{
	public:
		TextCursor(MBoundaries* InBoundaries, std::function<std::vector<pxPoint>()> InCallback);
		virtual void Update() override;

		void SetVisibility(bool Visible);
		int GetPosition();
		void SetPosition(int InPosition);

	private:
		int Position;
		fColor OnColor;
		fColor OffColor;
		bool bVisible;
		std::chrono::system_clock::time_point PreviousToggle;
	};
}