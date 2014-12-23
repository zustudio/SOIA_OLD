
#include "stdafx.h"

#include "Data_StatedState.h"

using namespace IA;

/////////////////////////////////////////////////////////////////////////////////////////////////////
// init 
Data_StatedState::Data_StatedState(int NewObject, const std::string &NewText, DataType NewType) : Data(NewObject, NewText)
{
	Type = NewType;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// overrides
void Data_StatedState::NET_Connect(Data* NewData)
{
	Data_StatedState* newData = (Data_StatedState*)NewData;
	switch (newData->Type)
	{
		case DataType::Content:
		{
			Data_StatedState* link = new Data_StatedState(cIA_LinkContent, "", DataType::Link);
			link->Data::NET_Connect(this);
			link->Data::NET_Connect(NewData);
			this->Data::NET_Connect(link);
			NewData->Data::NET_Connect(link);
		} break;
		case DataType::Link:
		{
			Data::NET_Connect(NewData);
		}break;
	}
}
Data* Data_StatedState::NET_getConnected(int iData)
{
	return NET_getConnected(iData, LinkType::Both);
}

Data* Data_StatedState::NET_getConnected(int iData, LinkType WantedLink)
{
	switch (Type)
	{
		case DataType::Content:
		{
			Data_StatedState* link = (Data_StatedState*)Data::NET_getConnected(iData);
			if (!link) { std::cout << "[Data]: error: tried to access data[i] out of bounds\n"; return nullptr; }
#if cSO_DebugData >= 1
			if (link->NET_getConnectedNum() > 2) {std::cout << "[Data]: error: more than 2 connections of link\n";}
#endif
			if ((*link)[0] == this && (WantedLink == LinkType::Downlink || WantedLink == LinkType::Both))
			{
				return (*link)[1];
			}
			else if ((*link)[1] == this && (WantedLink == LinkType::Uplink || WantedLink == LinkType::Both))
			{
				return (*link)[0];
			}
			else
			{
				NET_getConnected(iData + 1, WantedLink);
			}
		} break;
		case DataType::Link:
		{
			return Data::NET_getConnected(iData);
		} break;
	}
}

int Data_StatedState::NET_getConnectedNum()
{
	return NET_getConnectedNum(LinkType::Both);
}
int Data_StatedState::NET_getConnectedNum(LinkType WantedLink)
{
	if (WantedLink == LinkType::Both || this->Type == DataType::Link)
	{
		return Data::NET_getConnectedNum();
	}

	int num = 0;
	for (int iD_Connected = 0; iD_Connected < NET_ConnectedData.size(); iD_Connected++)
	{
		if (NET_ConnectedData[iD_Connected]->NET_ConnectedData[0] == this && WantedLink == LinkType::Downlink)
			num++;
		else if (NET_ConnectedData[iD_Connected]->NET_ConnectedData[1] == this && WantedLink == LinkType::Uplink)
			num++;
	}
	return num;
}