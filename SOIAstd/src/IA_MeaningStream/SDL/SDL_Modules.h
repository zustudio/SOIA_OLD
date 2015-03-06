///////////////////////////////////////////////////////////
// Symbol Description Language - Modules
//  offers macros for usage of compounded IData classes
///////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////
// meta macros: (definitions used by 'real' macros in this language)
/*	name of global variable used for IData type checks */
#define MDLVECTOR gIA_RegisteredDataModules

///////////////////////////////////////////////////////////
// IData macros: to be used inside compounded data class
/*	to be called on every module of custom Data class
	inside of the constructor*/
#define registerM(module) MDLVECTOR.push_back(std::string(#module));

///////////////////////////////////////////////////////////
// ref macros: for Module references if IData interface is not sufficient
/*	registers global variable for current file*/
#define SDL_Modules_Init namespace IA { extern std::vector<std::string> MDLVECTOR; }

/*	checks whether module is available in current main data class*/
#define checkM(module) (std::find(MDLVECTOR.begin(), MDLVECTOR.end(), std::string(#module)) != MDLVECTOR.end())
