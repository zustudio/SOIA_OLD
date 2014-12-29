#pragma once

#include "Definitions.h"

#include "IData.h"

#define exEnum(enumname, operations) class enumname {private: int i; public: enumname(int newI = 0) { i = newI; } operator int() { return i; } operations }
#define enumElement(name, var) static const int name = var

namespace IA
{
	///////////////////////////////////////////////
	// type definitions
	exEnum(DataType, 
		enumElement(Content, 0);
		enumElement(Link, 1);
	);
	exEnum(LinkType,
		enumElement(Downlink, 1);
		enumElement(Uplink, 2);
	);

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
				default:/*case DataType::Link:*/
				{
					Super::connect(NewSub);
				} break;
			}
		}
		virtual IData* getConnected(int i = 0) override
		{
			return getConnected(i, LinkType::Uplink | LinkType::Downlink);
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
					if ((WantedLink & LinkType::Downlink) && (link->Type == DataType::Link) && (*link)[0] == this)
					{
						return (*link)[1];
					}
					else if ((WantedLink & LinkType::Uplink) && (link->Type == DataType::Link) && (*link)[1] == this)
					{
						return (*link)[0];
					}
					else
					{
						i++;
						return getConnected(i, WantedLink);
					}
				} break;
				default:/*case DataType::Link:*/
				{
					return Super::getConnected(i);
				} break;
			}
		}
		virtual int getConnectedNum() override
		{
			return getConnectedNum(LinkType::Downlink | LinkType::Uplink);
		}
		virtual int getConnectedNum(LinkType WantedLink)
		{
			if (/*WantedLink & (LinkType::Downlink | LinkType::Uplink) || */this->Type != DataType::Content)
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
