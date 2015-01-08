///////////////////////////////////////////////////////////
// Symbol Description Language - Structure
//	offers ability to describe Data structures
//	in an abstract, but easier readable way
//
//  coding conventions:
//	 1.	internal macros are written in UPPERCASE letters
//	 2. macros that are supposed to be used inside the
//		 engine are written wholly in lowercase letters
///////////////////////////////////////////////////////////

#include "Definitions.h"


///////////////////////////////////////////////////////////
// meta macros: (definitions used by 'real' macros in this language)
/*global type of the engine's data (new shortcut)*/
#define DATA cIA_Data
/*default content for categories*/
#define dVAL		SDL_dContent
#define dLISTVAL	SDL_dListHolderContent


///////////////////////////////////////////////////////////
/* initializer for SDL */
#define SDL_start	DATA*	tempSDL_pData0; \
					DATA*	tempSDL_pBackup0; \
					int		dVAL = 0; \
					int dLISTVAL = 111;

///////////////////////////////////////////////////////////
/* structure to create new data elements */
//----  symbol  ----
#define symbol		tempSDL_pData0 = new DATA(dVAL);

#define newsymbol	symbol \
					DATA* /*>>NameOfSymbol<<*/

#define endsymbol	;

//---- children ----
#define sub			; \
					tempSDL_pBackup0 = tempSDL_pData0; \
					tempSDL_pData0 = new DATA(dVAL);

#define newsub		sub \
					DATA* /*>>NameOfChild<<*/

#define endsub		; \
					*tempSDL_pBackup0 >> tempSDL_pData0; \
					tempSDL_pData0 = tempSDL_pBackup0;

//---- setting ----
#define is			= tempSDL_pData0; \
					*tempSDL_pData0 = /*>>NewContent<<*/

#define isdefault	is dVAL;

#define isllist(...)	= tempSDL_pData0; \
						*tempSDL_pData0 = dLISTVAL; \
						{ \
							int SDL_intList[] = {__VA_ARGS__}; \
							int n = sizeof(SDL_intList) / sizeof(int); \
							for (int i = 0; i < n; i++) \
							{ \
								DATA* add = new DATA(SDL_intList[i]); \
								*tempSDL_pData0 >> add; \
							} \
						}

//---- properties ----
#define setname(Name)	; \
						tempSDL_pData0->Text = new std::string(Name)

