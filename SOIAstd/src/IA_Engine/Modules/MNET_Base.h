#pragma once

#include "IData.h"

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
		// constructor
		MNET_Base(int NewContent = 0)
		{
			Content = NewContent;
			ConnectedData = std::deque<IData*>();
		}

		//////////////////////////////////////////////
		// implementation of IData Interface
		virtual int get() override				{ return Content; }
		virtual void set(int i) override		{ Content = i; }

		virtual void connect(IData* NewSub)		{ ConnectedData.push_back(NewSub); ((MNET_Base<Super>*)NewSub)->ConnectedData.push_back(this); }
		virtual IData* getConnected(int i = 0)	{ return i < ConnectedData.size() ? ConnectedData[i] : nullptr; }
		virtual int getConnectedNum()			{ return ConnectedData.size(); }
	};
}