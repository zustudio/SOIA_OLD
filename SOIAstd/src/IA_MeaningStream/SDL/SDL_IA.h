


/*	modules:
	 functionality:
	  - every module is a class derived from the IData Interface
	  - ^ implements functions (+ own helper functions)
	  - the SDL_IA creates a class stream of modules (e.g.: [IData] <-MData_Base<-MLinkType<-M<-Activation<- [Data_EngineX])
	  - this class stream provides functionality for the final Data_EngineX class
*/


/* define macros used by m4, so that they are not wrongly colored by realtime cpp compilers */
#define define(__va_args__)
#define changequote(__va_args__)
#define changecom()
#define divert(i)
#define dnl

/*settings for m4*/
changequote([, ])dnl
changequote(´, `)dnl
changecom(´/*`,´*/`)dnl
/*meta definitions*/
define(´CPPDEF`, #define)dnl
define(´CPPUNDEF`, #undef)dnl
define(´CPPINCL`, #include)dnl

/*Definition: module(>>NameOfClass<<)
	- for building modular Data Classes
	- gets expanded to:
		1. #define Super 'SuperClass'
		2. #include "'Current'.h"
		3. #undef Super
*/
divert(-1)dnl
	define(´SUPER`, void)
	define(´CURRENT`, IData)
	define(´module`, ´define(´SUPER`, CURRENT)`dnl
		´CPPDEF Super SUPER`
		´define(´CURRENT`, $1)`dnl
		´CPPINCL "CURRENT.h"`
		´CPPUNDEF Super`)
divert(1)dnl
//doing!!

module(Base)
module(MText)
module(MTypes)
module(MActivation)



/*	example syntax (not working [yet/never?]):

	SDL_IA_Start
	
	module1(MData_Base)
	module2(MTypes)
	module3(MActivation)

	datasection
		structure
			symbol knowledge isdefault
				newsub action is 1
					name("Action")
				endsub
				newsub result is 2
					name("result")
				endsub
			endsymbol
		endstructure

		actions
			newaction Main
				
			endaction
		endactions
	enddatasection

	enginesection

			newaction Main
				NewTo(Current)
				ForAll
					
					LightConnect(Current, All)
				EndForAll
				Activate

			endaction

	endenginesection

	SDL_IA_End
*/
