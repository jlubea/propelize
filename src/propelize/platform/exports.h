#ifndef PROPELIZE_EXPORTS_H
#define PROPELIZE_EXPORTS_H


#if defined(_LIB) || defined(STATIC_LIB)
# define PROPELIZE_API
#else
# ifdef PROPELIZE_EXPORTS
#  ifdef _WIN32
#   define PROPELIZE_API __declspec (dllexport)
#  endif
# else
#  ifdef _WIN32
#   define PROPELIZE_API __declspec (dllimport)
#  endif
# endif
#endif

// private stl members generate this warning.
#pragma warning (disable : 4251)
// must compile everything with the same compiler and c++ runtime
#pragma warning (disable : 4275)


#endif