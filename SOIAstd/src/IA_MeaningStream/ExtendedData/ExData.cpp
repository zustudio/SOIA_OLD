
#include "stdafx.h"

#include "IA_SSt.h"

#include "ExData.h"

#include "SDL_Modules.h"

using namespace IA;
using namespace IA::Def_MTypes;
using namespace IA::MeaningStream;

extern std::vector<std::string> IA::MDLVECTOR;

////////////////////////////////////////////////////////////////
// init
ExData::ExData(IData* NewSource, std::deque<ExData*>* AllObjects)
{
	CurrentSource = NewSource;
	CurrentAllObjects = AllObjects;

	HierarchicDistance = -1;
	Children = std::deque<ExData*>();
	Location = fPoint();
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
	}
	for (int iExD = 0; iExD < CurrentAllObjects->size(); iExD++)
	{
		if (std::find(dataList->begin(), dataList->end(), (*CurrentAllObjects)[iExD]->CurrentSource) != dataList->end())
		{
			exDataList->push_back((*CurrentAllObjects)[iExD]);
		}
	}
	return exDataList;
}
