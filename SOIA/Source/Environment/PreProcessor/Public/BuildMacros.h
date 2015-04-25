
#pragma once

#if def_BUILD_PROJECTNAME == def_PROJECT_NAME
#define DLLIMPEXP __declspec(dllexport)
#else
#define DLLIMPEXP __declspec(dllimport)
#endif

