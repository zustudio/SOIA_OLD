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
#include <stack>


///////////////////////////////////////////////////////////
// meta macros: (definitions used by 'real' macros in this language)
/*global type of the engine's data (new shortcut)*/
#define DATA cIA_Data
/*default content for categories*/
#define dVAL		SDL_dContent
#define dLISTVAL	SDL_dListHolderContent


///////////////////////////////////////////////////////////
/* initializer for SDL */
#define SDL_start	std::stack<DATA*>	SDLtempDATA = std::stack<DATA*>(); \
					DATA* Data; \
					DATA* Backup; \
					int		dVAL = 0; \
					int dLISTVAL = 111;

///////////////////////////////////////////////////////////
/* structure to create new data elements */
//----  symbol  ----
#define symbol		SDLtempDATA.push(new DATA(dVAL));

#define newsymbol	symbol \
					DATA* /*>>NameOfSymbol<<*/

#define endsymbol	; \
					SDLtempDATA.pop();

//---- children ----
#define sub			; \
					SDLtempDATA.push(new DATA(dVAL));

#define newsub		sub \
					DATA* /*>>NameOfChild<<*/

#define endsub		; \
					Data = SDLtempDATA.top(); \
					SDLtempDATA.pop(); \
					Backup = SDLtempDATA.top(); \
					*Backup >> Data;
//---- setting ----
#define is			= SDLtempDATA.top(); \
					*SDLtempDATA.top() = /*>>NewContent<<*/

#define isdefault	is dVAL;

#define isllist(...)	= SDLtempDATA.top(); \
						*SDLtempDATA.top() = dLISTVAL; \
						{ \
							int SDL_intList[] = {__VA_ARGS__}; \
							int n = sizeof(SDL_intList) / sizeof(int); \
							for (int i = 0; i < n; i++) \
							{ \
								DATA* add = new DATA(SDL_intList[i]); \
								*SDLtempDATA.top() >> add; \
							} \
						}

//---- properties ----
#define setname(Name)	; \
						SDLtempDATA.top()->Text = new std::string(Name)

