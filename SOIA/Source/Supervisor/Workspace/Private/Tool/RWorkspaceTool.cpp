
#include "Definitions.h"

#include "RWorkspaceTool.h"
using namespace Environment;
using namespace Supervisor;

#include "RGraphTool2D.h"
#include "PipelineTool.h"
#include "RConversionPipes.h"
#include "RGUI.h"
#include "StringMatch.h"

RWorkspaceTool::RWorkspaceTool(const RPointer<RDialogue>& InDialogue)
	: BaseType(InDialogue)
{
	GetElementReflectionProvider()->RegisterList<
		RGraphTool,
		PipelineTool,
		RConversionPipes>();
	ReflectAttributes();
}

bool RWorkspaceTool::cmd_listtypes()
{
	std::vector<TypeID> reflectedAtoms = GetAtomReflectionProvider()->GetTypeList();
	std::vector<TypeID> reflectedElements = GetElementReflectionProvider()->GetTypeList();

	for (auto type : reflectedAtoms)
	{
		Dialogue->WriteLine("Atom\t" + type.ToString());
	}

	for (auto type : reflectedElements)
	{
		Dialogue->WriteLine("Element\t" + type.ToString());
	}
	return true;
}

bool RWorkspaceTool::cmd_type(TypeID & OutType, const std::string & InTypeName)
{
	std::vector<TypeID> reflectedAtoms = GetAtomReflectionProvider()->GetTypeList();
	std::vector<TypeID> reflectedElements = GetElementReflectionProvider()->GetTypeList();
	auto types = std::move(reflectedAtoms);
	types.insert(types.end(), reflectedElements.begin(), reflectedElements.end());

	std::vector<std::string> typeStrings;
	for (auto type : types)
	{
		typeStrings.push_back(type.ToString());
	}

	std::string match = StringMatch::GetBest(InTypeName, typeStrings);

	OutType = TypeID(match);

	Dialogue->WriteLine("Matched type: " + match);

	return true;
}

bool RWorkspaceTool::cmd_create(const TypeID & InType, const std::string& InName, RContainer* const& InContainer)
{
	bool result = false;
	RClass* objectClass = GetElementReflectionProvider()->GetClass(InType);
	if (objectClass)
	{
		RElement* object = objectClass->GetDefaultObject();

		RTool* tool = dynamic_cast<RTool*>(object);
		if (tool)
		{
			tool->Dialogue = this->Dialogue;
		}

		std::string name = InName;

		if (name == "")
			name = InType.ToEasyString();
		if (Container == nullptr)
			Container = GetContainer();

		Container->Register(object, name);
		result = true;
	}
	return result;
}

bool RWorkspaceTool::cmd_gui(RTool * const & InTool)
{
	static_cast<RGUI*>(InTool->GuiClass->GetDefaultObject())->Start();
	return true;
}




