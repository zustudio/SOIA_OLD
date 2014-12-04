// c Maxim Urschumzew

///////////////////////////////////////////////////////////
// os dependencies
//--- setting windows class based on running os ---
#ifdef def_OSWindows
	#include "Window_Win.h"
	#define Window SO::Window_Win
#elif def_OSUbuntu
	#include "Window_Ubu.h"
	#define Window SO::Window_Ubu
#else
	#include "Window_Base.h"
	#define Window SO::Window_Base
#endif
