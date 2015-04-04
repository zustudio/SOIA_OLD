/*
 * Class IDebugObj: Can be implemented into custom classes, if those require runtime execution breaking
 */

#pragma once

//Super class
#include "IIComOut.h"

#include <string>
#include "ComService.h"

namespace SOIA
{
	class ConsoleService;
}

namespace SO
{
	class Thread;

	namespace Debug
	{
		////////////////////////////////////////////////////////////////////////////////////////
		// Enums
		//---- DebugLevel ----
		enum class EDebugLevel : int
		{
			Error,
			Warning,
			Info_MainFunction,
			Info_SubFunction,
			Info_Loop
		};

		////////////////////////////////////////////////////////////////////////////////////////
		// Main class
		class IIDebuggable : virtual public Com::IIComOut
		{
			friend class SOIA::ConsoleService;

		public:
			////////////////////////////////////////////////////////////
			// functions
			//---- init ----
			IIDebuggable(SO::Com::ComService* NewUp = nullptr);
			void init(SO::Com::ComService* NewUp);
			//---- to be called by child class, at breakable code ----
			virtual void ii_Break(const std::string &message = "");
			void ii_Log(EDebugLevel level, const std::string &message);

			////////////////////////////////////////////////////////////
			// ICom interface complementation
			virtual void cGetCommands(std::vector<Handle<ICmd> > &Commands) override {};

		protected:
			////////////////////////////////////////////////////////////
			// variable access
			//---- getters ----
			bool GetBreakEnabled();
			//---- setters ----
			void ii_SetBreakPointsEnabled(bool bNewEnabled);

			Handle<ICom>* hndl;

		private:
			////////////////////////////////////////////////////////////
			// variables
			//---- communication ----
			Com::ComService* Up;
			//---- activation state ----
			bool bEnabled;
		};

		
	}
}
