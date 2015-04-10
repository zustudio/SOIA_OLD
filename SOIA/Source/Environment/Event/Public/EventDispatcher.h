
#pragma once

// include SOIA classes
#include "EventHandler.h"
#include "Event.h"

// include std classes
#include <vector>

namespace Environment
{
class EventDispatcher
{
public:
	//////////////////////////////////////////////////////////////
	// Init

	EventDispatcher(EventHandler* InHandlerToRegister = nullptr);
	virtual ~EventDispatcher();

	//////////////////////////////////////////////////////////////
	// Events

	/**	Dispatches passed Event to EventHandlers.
	 * 	Iterates over registered EventHandlers, calling their Handle(Event)
	 * 	function.
	 * 	@param[in] InEvent Event to be raised.
	 */
	void RaiseEvent(const Event &InEvent);

	//////////////////////////////////////////////////////////////
	// Handlers

	/**	Registers EventHandler.
	 * 	Passed EventHandler will now be called every time an event is
	 * 	raised.
	 * 	@param[in] InHandleToRegister EventHandler to be registered.
	 */
	void RegisterHandler(EventHandler* InHandleToRegister);


private:
	std::vector<EventHandler*> RegisteredEventHandlers;
};
}
