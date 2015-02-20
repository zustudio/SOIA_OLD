#pragma once

#include "IData.h"

#include <algorithm>
#include <deque>


namespace IA
{
	template<class Super>
	class MNET_Base : public Super
	{
	public:
		///////////////////////////////////////////////
		// content
		int Content;
		std::deque<IData*> ConnectedData;

		//////////////////////////////////////////////
		// con-/de-structor
		MNET_Base(int NewContent = 0)
		{
			Content = NewContent;
			ConnectedData = std::deque<IData*>();
		}
		virtual void Destroy() override
		{
			int n = MNET_Base::getConnectedNum();
			for (int i = 0; i < n; i++)
			{
				MNET_Base::disconnect(MNET_Base::getConnected(i));
			}
		}

		//////////////////////////////////////////////
		// implementation of IData Interface
		virtual int get() override				{ return Content; }
		virtual void set(int i) override		{ Content = i; }

		virtual void connect(IData* NewSub)
		{
			ConnectedData.push_back(NewSub);
			((MNET_Base<Super>*)NewSub)->ConnectedData.push_back(this);
		}
		virtual void disconnect(IData* OldSub)
		{
			MNET_Base<Super>* oldSub = (MNET_Base<Super>*)OldSub;
			if (isChild(oldSub))
			{
				oldSub->ConnectedData.erase(std::find(oldSub->ConnectedData.begin(), oldSub->ConnectedData.end(), this));
			}
		}
		virtual IData* getConnected(int i = 0)	{ return (i < ConnectedData.size() && i >= 0) ? ConnectedData[i] : nullptr; }
		virtual int getConnectedNum()			{ return ConnectedData.size(); }

		template<typename... Args>
			bool isChild(IData* TestSub, Args&&... args)	{ return (std::find(ConnectedData.begin(), ConnectedData.end(), TestSub) != ConnectedData.end()); }
	};
}
