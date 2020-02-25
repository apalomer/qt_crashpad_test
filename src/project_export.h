#pragma once

#if defined(_WIN32) || defined(_WIN64) || defined(WINCE) || defined(__MINGW32__)
#pragma warning(disable : 4251)
#define PROJECT_EXPORT __declspec(dllexport)
#define PROJECT_IMPORT __declspec(dllimport)
#else
#define PROJECT_EXPORT
#define PROJECT_IMPORT
#endif