
// include class
#include "EventDispatcher.h"
using namespace Environment;

//////////////////////////////////////////////////////////////////
// Init
EventDispatcher::EventDispatcher(EventHandler* InHandlerToRegister)
{
	RegisterHandler(InHandlerToRegister);
}
EventDispatcher::~EventDispatcher()
{

}

//////////////////////////////////////////////////////////////////
// Events
void EventDispatcher::RaiseEvent(const Event &InEvent)
{
	for (EventHandler* handler : RegisteredEventHandlers)
	{
		handler->Handle(InEvent);
	}
}

//////////////////////////////////////////////////////////////////
// Handlers
void EventDispatcher::RegisterHandler(EventHandler* InHandleToRegister)
{
	if (InHandleToRegister)
	{
		RegisteredEventHandlers.push_back(InHandleToRegister);
	}
}
