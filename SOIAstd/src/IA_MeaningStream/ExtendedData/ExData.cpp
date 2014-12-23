#include "stdafx.h"
#include <deque>
#include "ExData.h"

using namespace IA::MeaningStream;

////////////////////////////////////////////////////////////////
// init
ExData::ExData(cIA_Data* NewSource, std::deque<ExData*>* AllObjects) : Data_StatedState(*NewSource)
{
	CurrentSource = NewSource;
	CurrentAllObjects = AllObjects;

	HierarchicDistance = -1;
	Children = std::deque<ExData*>();
	Location = fPoint();
}

std::deque<ExData*>* ExData::getConnected(Data_StatedState::LinkType ConnectionType)
{
	std::deque<Data*>* dataList = new std::deque<Data*>();
	std::deque<ExData*>* exDataList = new std::deque<ExData*>();
	int n = CurrentSource->NET_getConnectedNum(ConnectionType);
	for (int iD = 0; iD < n; iD++)
	{	
		dataList->push_back(CurrentSource->NET_getConnected(iD, ConnectionType));
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
