
#pragma once

// include super class
#include "Environment/Reflection/ID/Public/RApplication.h"

// include SOIA
#include "Environment/Reflection/ID/Public/RFunction.h"

namespace Apprentice
{
	class DLLIMPEXP Engine : public Environment::RApplication
	{
	public:
		////////////////////////////////////////////////////////////////
		// Functions
		//----- Initializing -----

		/// Constructor.
		Engine(Environment::RContainer& InServiceContainer);

		/// Application entry point.
		virtual void Main() override final;

		//----- Engine routines -----

		/// Call to engine initializing.
		virtual void Init() = 0;

		/// call to engine tick.
		virtual void Tick() = 0;

		//----- Registered Functions -----
		bool cmd_Add(int Number);

	private:
		////////////////////////////////////////////////////////////////
		// Variables
		//----- status description -----

		/// Number of Tick calls left.
		int LeftTickNum;
	};
}