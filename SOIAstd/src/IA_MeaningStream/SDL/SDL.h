///////////////////////////////////////////////////////////
// Symbol Description Language
//	offers ability to describe Data structures
//	in an abstract, but easier readable way
//
//  coding conventions:
//	 1.	internal macros are written in UPPERCASE letters
//	 2. macros that are supposed to be used inside the
//		 engine are written wholly in lowercase letters
///////////////////////////////////////////////////////////

#include "Data.h"
#include "Definitions.h"


///////////////////////////////////////////////////////////
// meta macros: (definitions used by 'real' macros in this language)
/*global type of the engine's data (new shortcut)*/
#define DATA cIA_Data
/*default content for categories*/
#define dCAT_CONTENT 1000


///////////////////////////////////////////////////////////
/* initializer for SDL */
#define SDL_start	DATA* tempSDL_pData0; \
					DATA* tempSDL_pBackup0;

///////////////////////////////////////////////////////////
/* structure to create new data elements*/
//----  symbol  ----
#define symbol		tempSDL_pData0 = new DATA(dCAT_CONTENT);

#define newsymbol	category \
					DATA* /*>>NameOfSymbol<<*/

#define endsymbol	;

//---- children ----
#define sub			; \
					tempSDL_pBackup0 = tempSDL_pData0; \
					tempSDL_pData0 = new DATA(dCAT_CONTENT);

#define newsub		sub \
					DATA* /*>>NameOfChild<<*/

#define endsub		; \
					*tempSDL_pBackup0 >> tempSDL_pData0; \
					tempSDL_pData0 = tempSDL_pBackup0;

//---- setting ----
#define is			= tempSDL_pData0; \
					*tempSDL_pData0 = /*>>NewContent<<*/

#define isdefault	is dCAT_CONTENT;

