
#pragma once

// include super class
#include "RFunctionInterface.h"

// include SOIA
#include "Environment/Reflection/TypeAttribute/Public/VoidPointer.h"

// include std
#include <vector>

namespace Environment
{
	template <class TargetObjectType, typename ...ArgumentTypes>
	class DLLIMPEXP RFunction : public RFunctionInterface
	{
	public:

		////////////////////////////////////////////////////////////////
		// Definitions
		typedef bool(TargetObjectType::* TargetFunctionPointerType)(ArgumentTypes...);

		template<typename Type>	struct CleanTypePointer
		{
		public:
			CleanTypePointer() : Pointer(nullptr) {}
			typename std::decay<Type>::type* Pointer;
		};

		////////////////////////////////////////////////////////////////
		// Functions
		//----- Initializing -----

		/// Constructor.
		RFunction(TargetObjectType* InTargetObject, TargetFunctionPointerType InTargetFunction)
		{
			TargetObject = InTargetObject;
			TargetFunction = InTargetFunction;
		}

		//----- Executing -----

		/// Execute via predefined types.
		virtual bool Execute(ArgumentTypes... Args)
		{
			return (TargetObject->*TargetFunction)(Args...);
		}
	
		/// Execute via dynamic type application.
		virtual bool Execute(const std::vector<SO::Base::VoidPointer> &InArgs) override
		{
			return MatchArgumentsAndExecute(InArgs, (CleanTypePointer<ArgumentTypes>().Pointer)...);
		}

	private:
		//----- Helper Functions -----
		/// Function for matching generic type vector to pre defined types then executing.
		template<typename... p_Argument_Types>
		bool MatchArgumentsAndExecute(const std::vector<SO::Base::VoidPointer>& TestArguments, p_Argument_Types... p_Arguments)
		{
			if (TestArguments.size() == sizeof...(p_Argument_Types))
			{
				if (rec_MatchArgument(TestArguments.begin(), p_Arguments...))
					return Execute(*p_Arguments...);
			}
			return false;
		}

		/// NOP function.
		bool rec_MatchArgument(std::vector<SO::Base::VoidPointer>::const_iterator i_TestArgument)
		{
			return true;
		}

		/// Recursively sets passed pointers to correctly casted members of TestArgument vector.
		template<typename FirstArgument_Type, typename... TailArguments_Types>
		bool rec_MatchArgument(std::vector<SO::Base::VoidPointer>::const_iterator i_TestArgument, FirstArgument_Type*& p_FirstArgument, TailArguments_Types*&... p_TailArguments)
		{
			p_FirstArgument = i_TestArgument->CastTo<FirstArgument_Type>();
			if (p_FirstArgument)
			{
				if (sizeof...(TailArguments_Types))
				{
					return rec_MatchArgument(i_TestArgument + 1, p_TailArguments...);
				}
				else
				{
					return true;
				}
			}	
			return false;
		}

		////////////////////////////////////////////////////////////////
		// Variables

		/// Function pointer to real function.
		TargetObjectType* TargetObject;
		TargetFunctionPointerType TargetFunction;
	};
}
