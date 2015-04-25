
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

// include class
#include "Environment/Reflection/ID/Public/RElement.h"
using namespace Environment;

void RElement::SetID(Element_ID InID)
{
	ID = InID;
}

Element_ID& RElement::GetID()
{
	return ID;
}
