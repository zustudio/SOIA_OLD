#include "Data.h"

using namespace IA;

#include <deque>

///////////////////////////////////////////////
// non linear - net - data management

void Data::NET_AddSequence(std::deque<int> &NewContent)
{
	Data* newData;
	Data* currentData = this;
	for (int i = 0; i < NewContent.size(); i++)
	{
		newData = new Data(NewContent[i]);
		currentData->NET_Connect(newData);
		currentData = newData;
	}
}
void Data::NET_Add(int NewContent)
{
	NET_Connect(new Data(NewContent));
}
void Data::NET_Connect(Data* NewData)
{
	//NewData->NET_ConnectedData.push_back(this);
	NET_ConnectedData.push_back(NewData);
}

void Data::NET_Disconnect(Data* Data)
{
	int size = NET_ConnectedData.size();
	for (int i = 0; i < size; i++)
	{
		if (NET_ConnectedData[i] == Data)
		{
			NET_ConnectedData.erase(NET_ConnectedData.begin() + i);
		}
	}
}
void Data::NET_DisconnectAll()
{
	int size = NET_ConnectedData.size();
	for (int i = 0; i < size; i++)
	{
		NET_ConnectedData.pop_back();
	}
}


int Data::NET_getConnectedNum()
{
	return NET_ConnectedData.size();
}

Data* Data::NET_getConnected(int Num)
{
	return NET_ConnectedData[Num];
}


///////////////////////////////////////////////
// init
Data::Data()
{
	Content = 0;
}
Data::Data(int NewObject, std::string NewText)
{
	Content = NewObject;
	if (NewText != "")
		Text = new std::string(NewText);
	else
		Text = nullptr;
}
