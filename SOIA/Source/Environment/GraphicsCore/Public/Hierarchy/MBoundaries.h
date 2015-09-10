
#pragma once

#include "MBound.h"

namespace Environment
{
	class LIBIMPEXP MBoundaries : public MBound
	{
		friend MBound;

	public:
		MBoundaries(MBoundaries* InBoundaries, pxMargins InMargins);
		virtual void MarkDirty() override;

		virtual MBoundaries* GetTopBoundaries() override;

	protected:
		void AddBoundObject(MBound* InBoundObject);

	private:
		std::vector<MBound*> BoundObjects;
	};
}