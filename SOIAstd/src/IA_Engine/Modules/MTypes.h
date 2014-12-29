#pragma once

#include "Definitions.h"

#include "IData.h"

namespace IA
{
	///////////////////////////////////////////////
	// type definitions
	enum class DataType
	{
		Content,
		Link
	};
	enum class LinkType
	{
		Both,
		Uplink,
		Downlink
	};

	template <class Super>
	class MTypes : public Super
	{
	public:
		///////////////////////////////////////////////
		// properties
		DataType Type;

		///////////////////////////////////////////////
		// init
		template<typename... Args>
		MTypes(DataType NewType, Args&&... args) : Super(args...) { Type = NewType; }

		///////////////////////////////////////////////
		// overrides
		virtual void connect(IData* NewSub) override
		{
			switch (((MTypes<Super>*)NewSub)->Type)
			{
			case DataType::Content:
			{
				MTypes<Super>* link = new MTypes<Super>(DataType::Link, cIA_LinkContent);
				this->Super::connect(link);
				link->Super::connect(NewSub);
			} break;
			case DataType::Link:
			{
				Super::connect(NewSub);
			} break;
			}
		}
		virtual IData* getConnected(int i = 0) override
		{
			return getConnected(i, LinkType::Both);
		}
		virtual IData* getConnected(int &i, LinkType WantedLink)
		{
			switch (Type)
			{
				case DataType::Content:
				{
					MTypes<Super>* link = (MTypes<Super>*)Super::getConnected(i);
					if (!link) { /*std::cout << "[Data]: error: tried to access data[i] out of bounds\n";*/ return nullptr; }
#if cSO_DebugData >= 1
				if (link->getConnectedNum() > 2) { std::cout << "[Data]: error: more than 2 connections of link\n"; }
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
					i++;
					return getConnected(i, WantedLink);
				}
			} break;
			case DataType::Link:
			{
				return Super::getConnected(i);
			} break;
			}
		}
		virtual int getConnectedNum() override
		{
			return getConnectedNum(LinkType::Both);
		}
		virtual int getConnectedNum(LinkType WantedLink)
		{
			if (WantedLink == LinkType::Both || this->Type == DataType::Link)
			{
				return Super::getConnectedNum();
			}

			int i = 0;
			int tryAt = 0;
			while (getConnected(tryAt, WantedLink) != nullptr)
			{
				tryAt++;
				i++;
			}
			return i;
		}


	};
}
