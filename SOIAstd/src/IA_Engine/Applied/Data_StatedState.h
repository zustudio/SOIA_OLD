
#pragma once

#include "Data.h"

namespace IA
{
	class Data_StatedState : public Data
	{
	public:
		/////////////////////////////////////////////
		// data
		/*describes the type of this Data element
			Content	= 0		simple Data
			Link	= 1		connection between two simple datas (*this[0] is uplink, *this[1] is downlink)
		*/
		enum DataType
		{
			Content,
			Link
		};
		DataType Type;
		enum LinkType
		{
			Both,
			Uplink,
			Downlink
		};

		/////////////////////////////////////////////
		// functions
		//---- init ----
		Data_StatedState(int NewObject, const std::string &NewText = "", DataType NewType = DataType::Content);
		//---- overrides ----
		virtual void NET_Connect(Data* NewData) override;
		virtual int NET_getConnectedNum() override;
		int NET_getConnectedNum(LinkType WantedLink);
		virtual Data* NET_getConnected(int iData) override;
		Data* NET_getConnected(int iData, LinkType WantedLink);

	};
}