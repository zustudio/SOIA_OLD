// c Maxim Urschumzew

///////////////////////////////////////////////////////////
// os dependencies
//--- setting windows class based on running os ---
#ifdef def_OSWindows
	#define Window SO::Window_Win
#else
	#define Window SO::Window_Base
#endif