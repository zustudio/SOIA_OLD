
/*	modules:
	 functionality:
	  - every module is a class derived from the IData Interface
	  - ^ implements functions (+ own helper functions)
	  - the SDL_IA creates a class stream of modules (e.g.: [IData] <-MData_Base<-MLinkType<-M<-Activation<- [Data_EngineX])
	  - this class stream provides functionality for the final Data_EngineX class
*/

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
