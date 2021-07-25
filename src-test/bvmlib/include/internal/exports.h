#ifndef __BVM_INTERNAL_EXPORTS
#define __BVM_INTERNAL_EXPORTS
#if defined(_WIN32) || defined(WIN32)
#ifdef BVMLIB_EXPORTS
#define BVMLIB_DECL __declspec(dllexport)
#else
#define BVMLIB_DECL __declspec(dllimport)
#endif
#else
#define BVMLIB_DECL
#endif
#endif