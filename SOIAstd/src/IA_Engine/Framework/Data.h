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
		// set & get (operators)
		//  -content
		Data* operator =(int NewContent)		{ Content = NewContent; return this; }
		operator int()							{ return Content; }
		//  -children
		Data* operator[] (int iData)			{ return NET_getConnected(iData); }
		Data* operator>> (Data* NewChild)		{ NET_Connect(NewChild); return this; }
		
		// set (functions)
		void NET_AddSequence(std::deque<int>&);
		void NET_Add(int);
		virtual void NET_Connect(Data* NewData);
		void NET_Disconnect(Data* Data);
		void NET_DisconnectAll();
		// get (functions)
		virtual Data* NET_getConnected(int Num);
		virtual int NET_getConnectedNum();

		//----       init         ----
		Data(int NewObject = 0, const std::string &NewText = "");
		
	};

}