#pragma once

#include <deque>
#include <string>

namespace IA
{
	class Data
	{
	public:
		//####################################################################################
		//######################### non linear - net data management #########################
		//####################################################################################
		////////////////////////////////////////////////
		// data
		std::deque<Data*> NET_ConnectedData;
		int Content;
		std::string* Text;

		///////////////////////////////////////////////
		// functions

		//---- public data access ----
		// set
		void NET_AddSequence(std::deque<int>&);
		void NET_Add(int);
		void NET_Connect(Data* NewData);
		void NET_Disconnect(Data* Data);
		void NET_DisconnectAll();
		// get
		Data* NET_getConnected(int Num);
		int NET_getConnectedNum();

		//----       init         ----
		Data();
		Data(int NewObject, std::string NewText = "");
	};

}