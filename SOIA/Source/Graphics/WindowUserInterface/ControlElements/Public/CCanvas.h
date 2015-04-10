/*
 * CCanvas.h
 *
 *  Created on: Dec 6, 2014
 *      Author: mxu
 */

#pragma once

#include "Control.h"
#include "fColor.h"
#include <deque>

namespace Graphics
{
	class fPoint;
	class fColor;
	class fCanvasObject;

	class __declspec(dllexport) CCanvas : public Control
	{
	public:
		/////////////////////////////////////////////////////////////////////////////////////
		// variables
		//---- draw ----
		std::deque<fCanvasObject*> Objects;

		/////////////////////////////////////////////////////////////////////////////////////
		// functions
		//---- init ----
		CCanvas(SO::Window_Base* newWindow = nullptr, const cPoint &newLoc = cPoint(), const cPoint &newSize = cPoint());
		//---- loop ----
		virtual void Draw() override;
	private:
		void DrawRegisteredObjects();
		void DrawSingleRegisteredObject(fCanvasObject* InObject, std::vector<fCanvasObject*> &OutTempObjectList);
		//---- draw ----
	public:
		void DrawRect(const fPoint &a, const fPoint &size, const fColor &color = fColor(0, 0, 0));
		void DrawFilledRect(const fPoint &a, const fPoint &size, const fColor &color = fColor(0, 0, 0));
		void DrawLine(const fPoint &a, const fPoint &b, const fColor &color = fColor(0, 0, 0));
		void CDrawText(const fPoint &a, std::string *text, const fColor &color = fColor(0, 0, 0));
		void DrawArrow(const fPoint &a, const fPoint &b, const fColor &color = fColor(0, 0, 0));
		void DrawObject(fCanvasObject* InObject);
		void HighlightObject(fCanvasObject* InObject, bool bEnable);
		void Clear();
		//---- calc ----
	private:
		cPoint getAbsCP(const fPoint &a, bool bDelta = false);
	};
}
