
#pragma once

#include "Event.h"

namespace Environment
{
class EventHandler
{
public:
	////////////////////////////////
	// Init

	EventHandler();
	virtual ~EventHandler();

	////////////////////////////////
	// Event

	/** Handles passed event.
	 *	This function is called by EventDispatchers. It tries
	 *	to call a specific registered eventhandler-method. It
	 *	may also be overriden to directly check for Events.
	 *	@param[in] InEvent Event to be handled.
	 */
	virtual void Handle(const Event &InEvent);

};
}
