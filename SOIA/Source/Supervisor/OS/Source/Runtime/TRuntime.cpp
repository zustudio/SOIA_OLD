
#include "Definitions.h"

#include "TRuntime.h"
using namespace Environment;
using namespace Supervisor;

#include "RGUI.h"
#include "StringMatch.h"
#include "FileSystemProvider.h"
#include "ElementFile.h"
#include "GlobalLogger.h"
#include "TConsole.h"
#include "TMainTool.h"
#include "PersistentRuntime.h"

TRuntime::TRuntime()
	: BaseType(),
	CurrentDirectory(Directory::ExecutableDirectory())
{
	ReflectAttributes();
}

bool TRuntime::cmd_start(RElement * const & InMainTool)
{
	TMainTool* mainTool = dynamic_cast<TMainTool*>(InMainTool);
	if (mainTool)
	{
		PersistentRuntime::ChangeMainTool(mainTool);
	}
	return (bool)mainTool;
}

bool TRuntime::cmd_typelist()
{
	std::vector<TypeID> reflectedAtoms = GlobalAtomConverterProvider()->GetTypeList();
	std::vector<TypeID> reflectedElements = GlobalRClassProvider()->GetTypeList();

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

bool TRuntime::cmd_type(TypeID & OutType, const std::string & InTypeName)
{
	std::vector<TypeID> types = GlobalRClassProvider()->GetTypeList();
	
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

bool TRuntime::cmd_create(const TypeID & InType, const std::string& InName, RContainer* const& InContainer)
{
	bool result = false;
	RClass* objectClass = GlobalRClassProvider()->GetClass(InType);
	RContainer* targetContainer = InContainer;
	if (objectClass)
	{
		RElement* object = objectClass->GetDefaultObject();

		/*TTool* tool = dynamic_cast<TTool*>(object);
		if (tool)
		{
			tool->Dialogue = this->Dialogue;
		}*/

		std::string name = InName;

		if (name == "")
			name = InType.ToEasyString();
		if (targetContainer == nullptr)
			targetContainer = GetContainer();

		targetContainer->Register(object, name);
		result = true;
	}
	return result;
}

bool TRuntime::cmd_rename(RElement* const& InElement, std::string const& InNewName)
{
	bool success = false;

	if (InElement)
	{
		InElement->GetName() = InNewName;
	}

	return success;
}

bool TRuntime::cmd_gui(TTool * const & InTool)
{
	//static_cast<RGUI*>(InTool->GuiClass->GetDefaultObject())->Start();
	return true;
}

bool TRuntime::cmd_dirlist()
{
	auto dirs = CurrentDirectory.GetSubDirectories(EDirectoryVisibility::All);
	for (auto dir : dirs)
	{
		Dialogue->WriteLine(dir.GetPath().GetName());
	}
	return true;
}

bool TRuntime::cmd_dir(Directory & OutDir, std::string const & InName)
{
	OutDir = Directory(Path(CurrentDirectory.GetPath().ToString() + InName + "/"));
	return true;
}

bool TRuntime::cmd_changedir(const Directory & InDir)
{
	CurrentDirectory = InDir;
	return true;
}

bool TRuntime::cmd_saveproject(Directory const& InDir)
{
	// get directory
	Directory dir = InDir;
	if (InDir.GetPath().ToString() == "")
	{
		dir = Directory(Directory::ExecutableDirectory().GetPath().AppendFolder("Pool").AppendFolder("Projects"));
	}

	// get project
	ElementID projectID = ElementID(0);
	RContainer* project = GlobalContainer()->GetElement<RContainer>(projectID);

	// save
	return SaveRecursive(dir, project);
}

bool TRuntime::SaveRecursive(Directory const & InDir, RElement* const& InElement)
{
	bool success = true;

	RContainer* InContainer = dynamic_cast<RContainer*>(InElement);
	if (InContainer)
	{
		Directory ContainerDir(Path(""));
		success &= SaveContainer(InDir, InContainer, ContainerDir);
		std::vector<RElement*> const & children = InContainer->GetAllElements<RElement>();
		for (RElement* const & child : children)
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

bool TRuntime::SaveContainer(Directory const & InDir, RContainer * const & InContainer, Directory & OutContainerDir)
{
	std::string folderName = InContainer->GetName();
	std::string fileName = folderName + ".cont";
	
	OutContainerDir = Directory(InDir.GetPath().AppendFolder(folderName));
	OutContainerDir.Create();

	ElementFile file = ElementFile(OutContainerDir.GetPath().AppendFile(fileName));
	file.Open(EFileMode::Overwrite);
	file.WriteSingle(InContainer, EElementSelectionMode::Single);
	file.Close();
	return true;
}

bool TRuntime::SaveElement(Directory const & InDir, RElement * const & InElement)
{
	std::string fileName = InElement->GetName() + ".elem";
	ElementFile file = ElementFile(InDir.GetPath().AppendFile(fileName));
	file.Open(EFileMode::Overwrite);
	file.WriteSingle(InElement, EElementSelectionMode::Single);
	file.Close();
	return true;
}

bool TRuntime::cmd_loadproject(Directory const & InDir)
{
	std::vector<RElement*> AllElements;
	LoadRecursive(InDir, AllElements);
	return false;
}

bool TRuntime::LoadRecursive(Directory const & InDir, std::vector<RElement*>& OutAllElements)
{
	std::vector<Directory> subDirectories = InDir.GetSubDirectories();
	std::vector<ElementFile> files = InDir.GetFiles<ElementFile>();

	for (Directory & subDirectory : subDirectories)
	{
		RContainer* container = nullptr;
		std::vector<RElement*> subElements;
		std::string containerElemFileName = subDirectory.GetPath().GetBaseName();
		auto iter_containerElemFile = Find(files, containerElemFileName, 
		[](const ElementFile& InSaveFile) -> std::string
		{
			return InSaveFile.GetPath().GetBaseName();
		});
		
		if (iter_containerElemFile != files.end())
		{
			LoadRecursive(subDirectory, subElements);
			LoadContainer(const_cast<ElementFile&>(*iter_containerElemFile), subElements, container);
			files.erase(iter_containerElemFile);
			OutAllElements.push_back(container);
		}
	}

	for (ElementFile file : files)
	{
		RElement* OutElement = nullptr;
		LoadElement(file, OutElement);
		OutAllElements.push_back(OutElement);
	}

	return true;
}

bool TRuntime::LoadContainer(ElementFile& InSaveFile, std::vector<RElement*> const & InChildren, RContainer *& OutContainer)
{
	InSaveFile.Open(EFileMode::Read);
	OutContainer = dynamic_cast<RContainer*>(InSaveFile.ReadSingle());
	return bool(OutContainer);
}

bool TRuntime::LoadElement(ElementFile& InSaveFile, RElement *& OutElement)
{
	InSaveFile.Open(EFileMode::Read);
	OutElement = InSaveFile.ReadSingle();
	return true;
}






