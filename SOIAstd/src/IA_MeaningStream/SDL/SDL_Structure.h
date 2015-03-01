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
//---- Names ----
/*global type of the engine's data (new shortcut)*/
#define DATA cIA_Data
/*default content for categories*/
#define dVAL		SDL_dContent
#define dLISTVAL	SDL_dListHolderContent
/*temp names for easier reference*/
#define PARENT		SDL_tempParent
//---- Helpers ----
/*macro for easier creation of VoidPointer to std:strings*/
#define p_TEXT(text) VoidPointer(*(new std::string(text)))
/*macro for easier creation of VoidPointer to IData*/
#define p_DATA(data) VoidPointer(*(static_cast<IData*>(data)))
/*macro for abstracted creation of new datas*/
#define NEWDATA(content) new DATA(content)


///////////////////////////////////////////////////////////
/* initializer for SDL */
#define SDL_start(create_groups)	std::stack<DATA*>	SDLtempDATA = std::stack<DATA*>(); \
					std::stack<std::string> SDLSUBTYPE = std::stack<std::string>(); \
					DATA* Data; \
					DATA* Backup; \
					DATA* PARENT; \
					int		dVAL = 0; \
					int dLISTVAL = 111; \
					bool bCreateGroups = create_groups; \
					std::vector<VoidPointer> SDLICOMARGS;
//std::string SDLSUBTYPE;

///////////////////////////////////////////////////////////
/* structure to create new data elements */
//----  symbol  ----
#define symbol		SDLtempDATA.push(NEWDATA(dVAL)); \
					if (bCreateGroups) cSend("MeaningSrvc", "convertdata", {p_DATA(SDLtempDATA.top()) } ); \
					if (bCreateGroups) cSend("MeaningSrvc", "addgroupstrings", {p_TEXT("SDLcreated"), p_TEXT("Equal"), p_DATA(SDLtempDATA.top()), 0, p_TEXT("DataPoints") } ); \
					PARENT = SDLtempDATA.top();

#define newsymbol	symbol \
					DATA* /*>>NameOfSymbol<<*/

#define endsymbol	; \
					SDLtempDATA.pop();

//---- children ----
#define sub			; \
					PARENT = SDLtempDATA.top(); \
					SDLtempDATA.push(NEWDATA(dVAL)); \
					*PARENT >> SDLtempDATA.top(); \
					if (bCreateGroups) cSend("MeaningSrvc", "convertdata", {VoidPointer(*(Engine*) this)}); \
					if (bCreateGroups) cSend("MeaningSrvc", "convertdata", {p_DATA(SDLtempDATA.top()) } );

#define newsub		sub \
					DATA* /*>>NameOfChild<<*/

#define endsub		; \
	 \
					Data = SDLtempDATA.top(); \
					SDLtempDATA.pop(); \
					Backup = SDLtempDATA.top();
					
//---- setting ----
#define is(content)	= SDLtempDATA.top(); \
					if (bCreateGroups) cSend("MeaningSrvc", "addgroupstrings", {p_TEXT("SDLcreated"), p_TEXT("Parentage"), p_DATA(SDLtempDATA.top()), p_DATA(PARENT), p_TEXT("DataPoints") } ); \
					SDLtempDATA.top()->set(content);

#define isdefault	is(dVAL);

#define isllist(...)	= SDLtempDATA.top(); \
						if (bCreateGroups) cSend("MeaningSrvc", "addgroupstrings", {p_TEXT("SDLcreated"), p_TEXT("Parentage"), p_DATA(SDLtempDATA.top()), p_DATA(PARENT), p_TEXT("List") } ); \
						SDLtempDATA.top()->set(dLISTVAL); \
						{ \
							int SDL_intList[] = {__VA_ARGS__}; \
							int n = sizeof(SDL_intList) / sizeof(int); \
							for (int i = 0; i < n; i++) \
							{ \
								DATA* add = NEWDATA(SDL_intList[i]); \
								*SDLtempDATA.top() >> add; \
							} \
						}

//---- properties ----
#define setname(Name)		; \
							SDLtempDATA.top()->Text = new std::string(Name)

#define setdebug(bEnable)	; \
							SDLtempDATA.top()->ii_SetBreakPointsEnabled(bEnable)

