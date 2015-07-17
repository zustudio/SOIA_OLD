
#include "Definitions.h"

#include "RWorkspaceTool.h"
using namespace Environment;
using namespace Supervisor;

#include "RGraphTool2D.h"
#include "PipelineTool.h"
#include "RConversionPipes.h"
#include "RGUI.h"
#include "StringMatch.h"
#include "FileSystemProvider.h"
#include "SaveFile.h"

RWorkspaceTool::RWorkspaceTool(const RPointer<RDialogue>& InDialogue)
	: BaseType(InDialogue),
	CurrentDirectory(GetFileSystem()->GetExecutableDirectory())
{
	GetElementReflectionProvider()->RegisterList<
		RGraphTool,
		PipelineTool,
		RConversionPipes>();
	ReflectAttributes();
}

bool RWorkspaceTool::cmd_typelist()
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

bool RWorkspaceTool::cmd_dirlist()
{
	auto dirs = CurrentDirectory.GetSubDirectories();
	for (auto dir : dirs)
	{
		Dialogue->WriteLine(dir.GetPath().GetName());
	}
	return true;
}

bool RWorkspaceTool::cmd_dir(Directory & OutDir, std::string const & InName)
{
	OutDir = Directory(Path(CurrentDirectory.GetPath().ToString() + InName + "/"));
	return true;
}

bool RWorkspaceTool::cmd_changedir(const Directory & InDir)
{
	CurrentDirectory = InDir;
	return true;
}

bool RWorkspaceTool::cmd_saveproject(Directory const& InDir)
{
	return SaveRecursive(InDir, GetTopContainer());
}

bool RWorkspaceTool::SaveRecursive(Directory const & InDir, RElement* const& InElement)
{
	bool success = true;

	RContainer* InContainer = dynamic_cast<RContainer*>(InElement);
	if (InContainer)
	{
		Directory ContainerDir(Path(""));
		success &= SaveContainer(InDir, InContainer, ContainerDir);
		std::vector<RElement*>& children = InContainer->GetAllElements<RElement>();
		for (RElement*& child : children)
		{
			success &= SaveRecursive(ContainerDir, child);
		}
	}
	else
	{
		success = SaveElement(InDir, InElement);
	}
	return success;
}

bool RWorkspaceTool::SaveContainer(Directory const & InDir, RContainer * const & InContainer, Directory & OutContainerDir)
{
	std::string folderName = InContainer->GetID().Name + ".cont";
	std::string fileName = InContainer->GetID().Name + ".elem";
	
	OutContainerDir = Directory(InDir.GetPath().AppendFolder(folderName));
	OutContainerDir.Create();

	SaveFile file = SaveFile(InDir.GetPath().AppendFile(fileName));
	file.AddElement(InContainer, ESaveMode::Single);
	file.Write();
	return true;
}

bool RWorkspaceTool::SaveElement(Directory const & InDir, RElement * const & InElement)
{
	std::string fileName = InElement->GetID().Name + ".elem";
	SaveFile file = SaveFile(InDir.GetPath().AppendFile(fileName));
	file.AddElement(InElement, ESaveMode::Recursive);
	file.Write();
	return true;
}




