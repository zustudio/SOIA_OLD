
#pragma once

// include LIBIMPEXP macro for library symbol export
#include "LibImpExpMacros.generated.h"

// include generic cpp language extensions
#include "CPPExtensions.h"

// macros for generating literal strings from macros
#define MACRO_TO_LITERAL_INTERNAL(arg)      #arg
#define MACRO_TO_LITERAL(name) MACRO_TO_LITERAL_INTERNAL(name)

// project name as literal macro
#define PROJECTNAME_LITERAL MACRO_TO_LITERAL(def_BUILD_PROJECTNAME)

