#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#ifdef PSL_DEV_ENV
#define PSL_LIBRARY __declspec(dllexport)
#else
#define PSL_LIBRARY __declspec(dllimport)
#endif
