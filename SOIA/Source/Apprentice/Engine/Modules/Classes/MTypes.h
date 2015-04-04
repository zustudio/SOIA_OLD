#pragma once


#include "IData.h"

/* custom extendable enum class */
#define exEnum(enumname, operations) class enumname {private: int i; public: enumname(int newI = 0) { i = newI; } operator int() { return i; } operations }
#define enumElement(name, var) static const int name = var


namespace IA
{
	///////////////////////////////////////////////
	// type definitions
	exEnum(DataType, 
		enumElement(Content, 0);
		enumElement(Link, 1);
		enumElement(LightLink, 2);
	);
	exEnum(LinkType,					//bitfield => values = 1, 2, 4,...
		enumElement(NoLink, 1 << 0);		// values describe the functions of linkage data
		enumElement(Downlink, 1 << 1);		//  |
		enumElement(Uplink, 1 << 2);		//  |

		enumElement(T_NormLink, 1 << 8);		// values describe the type of linkage data (LinkType::NormLink => DataType::Link)
		enumElement(T_LightLink, 1 << 9);

		enumElement(M_GreatesMatch, NoLink | Downlink | Uplink | T_NormLink | T_LightLink);
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
		MTypes(DataType NewType, Args&&... args) : Super(args...)
		{
			Type = NewType;
		}
		virtual ~MTypes() {}

		///////////////////////////////////////////////
		// overrides
		//--------------------------------------- interaction with children -----------------------------------
		virtual void connect(IData* NewSub) override
		{
			switch (((MTypes<Super>*)NewSub)->Type)
			{
				case DataType::Content:
				{
					MTypes<Super>* link = new MTypes<Super>(DataType::Link, nullptr, "" ,cIA_LinkContent);
					this->Super::connect(link);
					link->Super::connect(NewSub);
				} break;
				default:/*case DataType::Link:*/
				{
					Super::connect(NewSub);
				} break;
			}
		}
		virtual void disconnect(IData* OldSub) override
		{
			MTypes<Super>* oldSub = (MTypes<Super>*)OldSub;
			switch (oldSub->Type)
			{
				case DataType::Content:
				{
					if (isChild(OldSub, DataType::Content, LinkType::M_GreatesMatch))
					{
						int n_Links = Super::getConnectedNum();
						for (int i_Link = 0; i_Link < n_Links; i_Link++)
						{
							MTypes<Super>* link = (MTypes<Super>*)Super::getConnected(i_Link);
							if (link->isChild(oldSub, DataType::Content, LinkType::M_GreatesMatch & !(LinkType::Uplink | LinkType::Downlink)))
							{
								delete link;
								break;
							}
						}
					}
				}
				break;
				default: /*case DataType::SomeLink*/
				{
					Super::disconnect(OldSub);
				}
				break;
			}
		}
		virtual IData* getConnected(int i = 0) override
		{
			return getConnected(i, LinkType::T_NormLink | LinkType::Uplink | LinkType::Downlink);
		}
		virtual IData* getConnected(int i, LinkType AllowedLink)
		{
			//for (int i_Before = 0; i_Before <= i; i_Before++)				// neccessary? => counts up from zeroth element, if one element is not included, it does not count
			//{
			//	MTypes<Super>* lnkBefore = (MTypes<Super>*)Super::getConnected(i_Before);
			//	MTypes<Super>* dataBefore = lnkBefore->Super::getConnected(0) == this ? (MTypes<Super>*)lnkBefore->Super::getConnected(1) : (MTypes<Super>*)lnkBefore->Super::getConnected(0);
			//	if (!isChild(dataBefore, DataType::Content, AllowedLink))
			//		i++;
			//}

			int i_Before = -1;
			do				// neccessary? => counts up from zeroth element, if one element is not included, it does not count
			{
				i_Before++;
				MTypes<Super>* lnkBefore = (MTypes<Super>*)Super::getConnected(i_Before);
				if (!lnkBefore)
					return nullptr;
				MTypes<Super>* dataBefore = lnkBefore->Super::getConnected(0) == this ? (MTypes<Super>*)lnkBefore->Super::getConnected(1) : (MTypes<Super>*)lnkBefore->Super::getConnected(0);
				if (!isChild(dataBefore, DataType::Content, AllowedLink))
					i++;
			} while (i_Before < i);

			MTypes<Super>* conData = (MTypes<Super>*)Super::getConnected(i);

			if (conData == nullptr)
				return nullptr;

			if (isChild(conData, DataType::Content, AllowedLink))
				return conData;

			if (conData->Super::getConnected(1) != nullptr)
			{
				MTypes<Super>* Next = conData->Super::getConnected(0) == this ? (MTypes<Super>*)conData->Super::getConnected(1) : (MTypes<Super>*)conData->Super::getConnected(0);
				if (isChild(Next, DataType::Content, AllowedLink))
					return Next;
			}
	
			//return getConnected(i + 1, AllowedLink);
#if cSO_DebugData > 1
			std::cout << "[MTypes]: getConnected not returning";
#endif
			return nullptr;
		}


//			switch (Type)
//			{
//				case DataType::Content:
//				{
//					MTypes<Super>* link = (MTypes<Super>*)Super::getConnected(i);
//					if (!link) { /*std::cout << "[Data]: error: tried to access data[i] out of bounds\n";*/ return nullptr; }
//#if cSO_DebugData >= 1
//				if (link->getConnectedNum() > 2) { std::cout << "[Data]: error: more than 2 connections of link\n"; }
//#endif
//					if ((WantedLink & LinkType::Downlink) && (link->Type == DataType::Link) && (*link)[0] == this)
//					{
//						return (*link)[1];
//					}
//					else if ((WantedLink & LinkType::Uplink) && (link->Type == DataType::Link) && (*link)[1] == this)
//					{
//						return (*link)[0];
//					}
//					else
//					{
//						i++;
//						return getConnected(i, WantedLink);
//					}
//				} break;
//				default:/*case DataType::Link:*/
//				{
//					return Super::getConnected(i);
//				} break;
//			}

		virtual int getConnectedNum() override
		{
			return getConnectedNum(LinkType::T_NormLink | LinkType::Downlink | LinkType::Uplink);
		}
		virtual int getConnectedNum(LinkType AllowedLink)
		{
			int i = 0;
			int tryAt = 0;
			while (getConnected(tryAt, AllowedLink) != nullptr)
			{
				tryAt++;
				i++;
			}
			return i;
		}
			//if (/*WantedLink & (LinkType::Downlink | LinkType::Uplink) || */this->Type != DataType::Content)
			//{
			//	return Super::getConnectedNum();
			//}

		//------------------------------------- children tests -------------------------------------------------
		/*	returns true, if testchild has all wanted properties */
		template<typename... Args>
		bool isChild(IData* TestChild, DataType WantedType, LinkType AllowedLink, Args&&... args)
		{
			bool bMatching = false;

			if (AllowedLink & LinkType::NoLink)										// if child can be directly connected, only try super function
			{
				bMatching |= Super::isChild(TestChild, args...);
			}

			if (AllowedLink & (LinkType::Downlink | LinkType::Uplink))				// if child can be connected via link, test all link-connected children
			{
				int n = Super::getConnectedNum();
				for (int i = 0; i < n; i++)											//check every connected (link-) data, so that their properties can be matched:
				{
					MTypes<Super>* testLink = (MTypes<Super>*)Super::getConnected(i);
					bool bLinkMatching = false;

					if (!testLink->isChild(TestChild, WantedType, LinkType::NoLink))//check whether we have the right link data
						continue;

					if (AllowedLink & LinkType::T_NormLink)							// check whether the current link's datatype is allowed in WantedLink
						bLinkMatching |= isChild(testLink, DataType::Link, LinkType::NoLink);

					if (AllowedLink & LinkType::T_LightLink)
						bLinkMatching |= isChild(testLink, DataType::LightLink, LinkType::NoLink);
					
					if (bLinkMatching)
					{
						if (AllowedLink & LinkType::Downlink)						// check whether the upLink / downLink property is matching
						{
							bMatching |= (testLink->Super::getConnected(0) == this);
						}
						if (AllowedLink & LinkType::Uplink)
						{
							bMatching |= (testLink->Super::getConnected(1) == this);
						}
					}
				}
			}

			bMatching &= (((MTypes<Super>*)TestChild)->Type == WantedType);			// finaly check whether child's type equals wanted type

			return bMatching;
		}
	};
}
