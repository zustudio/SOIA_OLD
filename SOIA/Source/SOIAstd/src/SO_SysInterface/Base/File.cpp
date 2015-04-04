
#include "File.h"

using namespace SO;
using namespace SO::Base;

/////////////////////////////////////////////////////////////////
// init
File::File(const std::string &InName, const FileOptions &InOptions)
{
	Name = InName;
	Options = InOptions;
	OutStream->open(Name);
}

File::~File()
{
	OutStream->close();
}

//////////////////////////////////////////////////
// write to file
void File::Write()
{
	for (VoidPointer p_Obj : Content)
	{
		WriteObject(p_Obj);
	}
}

bool File::WriteObject(const VoidPointer &InObject)
{
	bool result = false;

	std::string* p_StrObj = InObject.CastTo<std::string>();
	int* p_IntObj = InObject.CastTo<int>();

	std::string tag;
	std::string out;

	if (p_StrObj)
	{
		out = *p_StrObj;
		tag = "<std::string>";
		result = true;
	}
	else if (p_IntObj)
	{
		out = std::to_string(*p_IntObj);
		tag = "<int>";
		result = true;
	}

	if (Options & FileOptions::TypeTags)
		*OutStream << tag;
	*OutStream << out.c_str() << '\n';
	

	return result;
}
