
#pragma once

#include "MBound.h"

namespace Environment
{
	class RenderTarget;
	class GraphicsWindow;
}

namespace Environment
{
	class LIBIMPEXP MBoundaries : public MBound
	{
		friend MBound;

	public:
		MBoundaries(MBoundaries* InBoundaries, pxMargins InMargins);
		virtual void RequestUpdate() override;
		virtual void Update() override;

		pxPoint GetScrollOffset();
		pxSize GetVirtualSize();
		void Scroll(pxPoint InOffset);
		virtual MBoundaries* GetTopBoundaries() override;

		//----- Events -----
		virtual void Event_VirtualSizeChanged(pxSize InNewSize);

	protected:
		RenderTarget* GetRenderTarget();
		GraphicsWindow* GetWindow();
		std::vector<MBound*>& GetBoundObjects();
		void AddBoundObject(MBound* InBoundObject);
		void RemoveBoundObject(MBound* InBoundObject);

	private:
		std::vector<MBound*> BoundObjects;
		pxPoint ScrollOffset;
		pxSize VirtualSize;
	};
}