
#pragma once
#include "Definitions.h"

#include "RElement.h"
#include "Function.h"
#include "DialogueInterface.h"
#include "ConstExprDynamicList.h"

#define ATTRIBUTE(object) \
template<> \
void RegisterObject<__COUNTER__>() \
{ \
	static constexpr const int myCount = __COUNTER__; \
	AttributeMirrors.push_back(new ObjectMirrorTemplate<decltype(object)>(object, #object )); \
	GetAtomReflectionProvider()->Reflect<decltype(object)>(); \
	RegisterObject<myCount - 3>(); \
};

namespace Supervisor
{

	RABSTRACTCLASS(RTool,Environment::RElement)
	class LIBIMPEXP RTool : public RTool_Base
	{
	public:
		RTool(DialogueInterface* InDialogue);

		template<int n>
		void RegisterObject()
		{

		};

		template<>
		void RegisterObject<__COUNTER__>()
		{
			static constexpr const int myCount = __COUNTER__;
		};

		int SomeInt;
		ATTRIBUTE(SomeInt);
		

		ATTRIBUTE(FloatingOn);
		std::vector<float> FloatingOn;

		


		ATTRIBUTE(cmd_Help_Interface);
		Environment::FunctionInterface* cmd_Help_Interface = new Function<RTool>(this, &RTool::cmd_Help);
		bool cmd_Help();

		void RegisterAllObjects()
		{
			RegisterObject<__COUNTER__ - 2>();
		}

	protected:
		DialogueInterface* Dialogue;
	};
}