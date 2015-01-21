
#include "Com_Handle.h"

using namespace SO::Com;

Com_Handle::Com_Handle(ICom* NewPointer, const std::string &NewName)
{
	Pointer = NewPointer;
	Name = std::string(NewName);
}
Com_Handle::~Com_Handle()
{
}