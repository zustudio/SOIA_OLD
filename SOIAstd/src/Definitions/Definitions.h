// c Maxim Urschumzew

//////////////////////////////////////////////////////////////////////////////////
// ai settings
/*	initial lenght of data link */
#define cIA_LinkContent 8

//////////////////////////////////////////////////////////////////////////////////
// versioning

/*  version of engine to be compiled
	0 -	base				(Data)
	1 - StatedState			(Data_StatedState)
*/
#define cIA_EngineVersion 1

/*sets the engine and data types accordingly to EngineVersion*/
#if cIA_EngineVersion == 0
	#define cIA_DataVersion		0
	#define cIA_Data			Data
	#define cIA_Engine			Engine
#elif cIA_EngineVersion == 1
	#define cIA_DataVersion		1
	#define cIA_Data			Data_SSt
	#define cIA_Engine			Engine_StatedState
#endif

//////////////////////////////////////////////////////////////////////////////////
// debugging
/*  the amount of dubug info displayed for DataExplorer
	0 - none
	1 - only basic
	2 - detailed information
*/
#define cSO_DebugDE 1

/*  debug info for Data
	0 - none
	1 - all
*/
#define cSO_DebugData 1

//////////////////////////////////////////////////////////////////////////////////
// os dependencies
//--- setting windows class based on running os ---
#ifdef def_OSWindows
	#include "Window_Win.h"
	#define Window_OS Window_Win
#elif def_OSUbuntu
	#include "Window_Ubu.h"
	#define Window_OS Window_Ubu
#else
	#include "Window_Base.h"
	#define Window_OS Window_Base
#endif
