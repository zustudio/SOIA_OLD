// c Maxim Urschumzew

//////////////////////////////////////////////////////////////////////////////////
// ai settings
/*	initial lenght of data link */
#define cIA_LinkContent 100

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
	#define cIA_Data			IData
	#define cIA_Engine			Engine
#elif cIA_EngineVersion == 1
	#define cIA_DataVersion		1
	#define cIA_Data			Data_SSt
	#define cIA_Engine			Engine_SSt
	#define cIA_Game			Game_StatedState
	#include "Game_SSt.h"
	#include "IA_SSt.h"
#endif

//////////////////////////////////////////////////////////////////////////////////
// debugging
/*  the amount of dubug info displayed for DataExplorer
	0 - none
	1 - only basic
	2 - detailed information
*/
#define cSO_DebugDE 2

/*  debug info for Data
	0 - none
	1 - only neccessary
	2 - all
*/
#define cSO_DebugData 1

