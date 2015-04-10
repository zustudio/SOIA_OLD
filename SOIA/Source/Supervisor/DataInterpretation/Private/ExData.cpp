
#include "stdafx.h"
#include "SDL.h"

#include "ExData.h"

using namespace IA;
using namespace IA::MeaningStream;

SDL_Modules_Init

////////////////////////////////////////////////////////////////
// init
ExData::ExData(IData* NewSource, std::deque<ExData*>* AllObjects) : fCanvasObject(CanvasObjT::Custom, fPoint(0,0), fPoint(0.1, 0.1), fColor(0, 1, 0))
{
	CurrentSource = NewSource;
	CurrentAllObjects = AllObjects;

	HierarchicDistance = -1;
	Children = std::deque<ExData*>();
	Location = fPoint();

	bHighlighted = false;
}

///////////////////////////////////////////////////////////////
// properties

std::string* ExData::getText()
{
	if (checkM(MText))
	{
		std::string* realText = ((cIA_Data*)CurrentSource)->Text;
		if (*realText != std::string(""))
		{
			return realText;
		}
	}
	return new std::string(std::to_string(int(*CurrentSource)));
}

std::deque<ExData*>* ExData::getConnected(LinkType ConnectionType)
{
	std::deque<IData*>* dataList = new std::deque<IData*>();
	std::deque<ExData*>* exDataList = new std::deque<ExData*>();

	int n;
	if (checkM(MTypes))
		n = ((cIA_Data*)CurrentSource)->getConnectedNum(ConnectionType);
	else
		n = CurrentSource->getConnectedNum();

	for (int iD = 0; iD < n; iD++)
	{
		IData* data;

		if (checkM(MTypes))
			data = ((cIA_Data*)CurrentSource)->getConnected(iD, ConnectionType);
		else
			data = CurrentSource->getConnected(iD);

		dataList->push_back(data);

		// find corresponding ExtendedData
		for (int iExD = 0; iExD < CurrentAllObjects->size(); iExD++)
		{
			if ((*CurrentAllObjects)[iExD]->CurrentSource == data)
			{
				exDataList->push_back((*CurrentAllObjects)[iExD]);
			}
		}
	}
	
	return exDataList;
}

////////////////////////////////////////////////////////////////////////////7
// custom parts interface
std::vector<fCanvasObject*>* ExData::GetCustomParts()
{
	while (CustomParts.size() > 0)
	{
		fCanvasObject* temp = CustomParts[CustomParts.size() - 1];
		CustomParts.pop_back();
		delete temp;
	}

	fPoint center = Vector2D<float>(InterpProps.FloatLocation);
	fPoint extend = Vector2D<float>(InterpProps.FloatExtend);
	fPoint Loc = fPoint(center.X - 0.5* extend.X, center.Y - 0.5*extend.Y);
	//fColor color = bHighlighted ? fColor(1, 0.2, 0.2) : fColor(0, 1, 0);
	if (bHighlighted)
		CustomParts.push_back(new fCanvasObject(CanvasObjT::FilledRectangle, Loc, extend, fColor(0.7, 0.75, 1.0)));
	else
		CustomParts.push_back(new fCanvasObject(CanvasObjT::Rectangle, Loc, extend, fColor(0,0,0)));

	std::string *text = getText();
	std::string* temp = new std::string(*text + " {" + std::to_string(CurrentSource->get()) + "}");
	CustomParts.push_back(new fCanvasObject(CanvasObjT::Text, Loc, Loc, fColor(0.1, 0.1, 0.5), temp));

	return &CustomParts;
}
void ExData::Highlight(bool bEnable)
{
	bHighlighted = bEnable;
}
