// compounded point class - for translation of pixeled and scaled points onto concrete windows
#pragma once

#include "fPoint.h"

namespace SO
{
	namespace Drawing
	{
		class pxPoint;
		class fPoint;

		class cPoint : fPoint
		{
		public:
			pxPoint* px;

			cPoint();
			cPoint(float fX, float fY, int pxX = 0, int pxY= 0);
			cPoint(const fPoint &newF, const pxPoint &newPx);
			~cPoint();

			virtual pxPoint ToPxPoint(const pxPoint &absolutSpaceSize) override;
		};
	}
}