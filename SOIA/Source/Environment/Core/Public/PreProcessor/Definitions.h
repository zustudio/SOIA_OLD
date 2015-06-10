
#pragma once

#include "LibImpExpMacros.generated.h"
#include "CPPExtensions.h"


#define MACRO_TO_LITERAL_INTERNAL(arg)      #arg
#define MACRO_TO_LITERAL(name) MACRO_TO_LITERAL_INTERNAL(name)

#define PROJECTNAME_LITERAL MACRO_TO_LITERAL(def_BUILD_PROJECTNAME)

