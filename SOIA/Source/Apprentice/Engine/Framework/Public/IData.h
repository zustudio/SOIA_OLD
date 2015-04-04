#pragma once

namespace IA
{
	class IData
	{
	public:
		//////////////////////////////////////////
		// abstract functions
		//---- destructor ----
		virtual void Destroy() = 0;
		//---- interaction with content ----
		virtual int get() = 0;
		virtual void set(int New) = 0;
		//---- interacting with children ----
		virtual void connect(IData* NewSub) = 0;
		virtual void disconnect(IData* OldSub) = 0;
		virtual IData* getConnected(int i = 0) = 0;
		virtual int getConnectedNum() = 0;
		//---- tests (of children) ----
		template<typename... Args>
		bool isChild(IData* TestSub, Args&&... args) { return false; }

		/////////////////////////////////////////
		// operators
		//  -content
		IData* operator =(int NewContent)		{ set(NewContent); return this; }
		operator int()							{ return get(); }
		//  -children
		IData* operator[] (int iData)			{ return getConnected(iData); }
		IData* operator>> (IData* NewChild)		{ connect(NewChild); return this; }
	};
}