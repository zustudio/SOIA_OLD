
#pragma once

// include super class
#include "RFunction.h"
#include "ReflectionProviders.h"

#define FUNCTION 

namespace Environment
{

	/// Reflect all argument types.
	template<typename...>
	struct ReflectArgumentTypes;

	template<>
	struct ReflectArgumentTypes<>
	{
		static void Do()
		{}
	};

	template<typename ArgumentType, typename... TailArgumentTypes>
	struct ReflectArgumentTypes<ArgumentType, TailArgumentTypes...>
	{
		static void Do()
		{
			GetAtomReflectionProvider()->Reflect<typename std::decay<ArgumentType>::type>();
			ReflectArgumentTypes<TailArgumentTypes...>::Do();
		}
	};

	template <class TargetObjectType, typename ...ArgumentTypes>
	class LIBIMPEXP RFunctionTemplate : public RFunction
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
		RFunctionTemplate(TargetObjectType* InTargetObject, TargetFunctionPointerType InTargetFunction, const std::string& InFuncName)
			:
			Name(InFuncName)
		{
			TargetObject = InTargetObject;
			TargetFunction = InTargetFunction;
			ReflectArgumentTypes<ArgumentTypes...>::Do();
		}

		//----- Executing -----

		/// Execute via predefined types.
		virtual bool Execute(ArgumentTypes... Args)
		{
			return (TargetObject->*TargetFunction)(Args...);
		}
	
		/// Execute via dynamic type application.
		virtual bool Execute(const std::vector<Environment::VoidPointer> &InArgs) override
		{
			return MatchArgumentsAndExecute(InArgs, (CleanTypePointer<ArgumentTypes>().Pointer)...);
		}

		//----- Information -----
		virtual std::vector<TypeID> GetArgumentTypes() override
		{
			return{ (TypeID::FromType<ArgumentTypes>())... };
		}
		virtual std::string GetName() override
		{
			return Name;
		}

	private:
		//----- Helper Functions -----
		/// Function for matching generic type vector to pre defined types then executing.
		template<typename... p_Argument_Types>
		bool MatchArgumentsAndExecute(const std::vector<Environment::VoidPointer>& TestArguments, p_Argument_Types... p_Arguments)
		{
			if (TestArguments.size() == sizeof...(p_Argument_Types))
			{
				if (rec_MatchArgument(TestArguments.begin(), p_Arguments...))
					return Execute(*p_Arguments...);
			}
			return false;
		}

		/// NOP function.
		bool rec_MatchArgument(std::vector<Environment::VoidPointer>::const_iterator i_TestArgument)
		{
			return true;
		}

		/// Recursively sets passed pointers to correctly cast members of TestArgument vector.
		template<typename FirstArgument_Type, typename... TailArguments_Types>
		bool rec_MatchArgument(std::vector<Environment::VoidPointer>::const_iterator i_TestArgument, FirstArgument_Type*& p_FirstArgument, TailArguments_Types*&... p_TailArguments)
		{
			p_FirstArgument = i_TestArgument->ConvertTo<FirstArgument_Type>();
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

		//name
		const std::string Name;
	};


	template <class TargetObjectType, typename... ArgumentTypes>
	decltype(auto) CreateFunction(TargetObjectType* InTargetObject, bool(TargetObjectType::* TargetFunctionPointer)(ArgumentTypes...), const std::string& InName)
	{
		return new RFunctionTemplate<TargetObjectType, ArgumentTypes...>(InTargetObject, TargetFunctionPointer, InName);
	}
}
