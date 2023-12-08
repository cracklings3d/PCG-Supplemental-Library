#pragma once

#ifdef PSL_DEV_ENV
#define PSL_LIBRARY __declspec(dllexport)
#else
#define PSL_LIBRARY __declspec(dllimport)
#endif
