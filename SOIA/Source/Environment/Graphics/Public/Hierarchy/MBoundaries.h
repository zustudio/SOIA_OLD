
#pragma once

#include "MBound.h"

#include "Interpolator.h"

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

		Interpolator<pxPoint> const & GetScrollOffset();
		pxSize GetVirtualSize();
		void Scroll(pxPoint InOffset);
		virtual MBoundaries* GetTopBoundaries() override;
		std::vector<MBound*> const & GetBoundObjects();

		//----- Events -----
		virtual void Event_VirtualSizeChanged(pxSize const & InNewSize);

	protected:
		RenderTarget* GetRenderTarget();
		GraphicsWindow* GetWindow();
		void AddBoundObject(MBound* InBoundObject);
		void RemoveBoundObject(MBound* InBoundObject);

	private:
		std::vector<MBound*> BoundObjects;
		Interpolator<pxPoint> ScrollOffset;
		pxSize VirtualSize;
	};
}