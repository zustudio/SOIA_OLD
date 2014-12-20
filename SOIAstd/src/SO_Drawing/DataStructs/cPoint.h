// compounded point class - for translation of pixeled and scaled points onto concrete windows
#pragma once

#include "fPoint.h"

namespace SO
{
	namespace Drawing
	{
		class pxPoint;
		class fPoint;

		class cPoint : public fPoint
		{
		public:
			pxPoint* px;

			//cPoint();
			cPoint(float fX, float fY, int pxX = 0, int pxY= 0);
			cPoint(const fPoint &newF = fPoint(), const pxPoint &newPx = pxPoint());
			~cPoint();

			float getFX();
			float getFY();

			virtual pxPoint ToPxPoint(pxPoint &absolutSpaceSize) override;
		};
	}
}
