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
			///////////////////////////////////////////////////////////////////////////////
			// data
			pxPoint* px;

			///////////////////////////////////////////////////////////////////////////////
			// functions
			//---- init ----
			cPoint(float fX, float fY, int pxX = 0, int pxY= 0);
			cPoint(const fPoint &newF = fPoint(), const pxPoint &newPx = pxPoint());
			~cPoint();
			//---- getter /setter ----
			float getFX();
			float getFY();
			//---- conversion ----
			cPoint(const Vector2D<float> a) {X = a.X; Y = a.Y; px = new pxPoint();}
			virtual pxPoint ToPxPoint(pxPoint &absolutSpaceSize) override;
			//---- math ----
			cPoint operator+(cPoint a)
			{
				cPoint r = Vector2D::operator+(a);
				*(r.px) += *(a.px);
				return r;
			}
		};
	}
}
