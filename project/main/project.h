#ifndef PROJECT_H
#define PROJECT_H

#if defined(_WIN32) || defined(__WIN32__)
#    define PLATFORM_WINDOWS
#elif defined(__linux__)
#    define PLATFORM_UNIX
#else
#    define PLATFORM_UNKNOWN
#endif

#define PRJ_DBG

#ifdef PRJ_DBG
#    define THREAD_COUNTERS_PRINT
// #    define TEXTURES_TEST
#endif

#if defined(PLATFORM_UNIX)
#    define THREAD_INIT
#endif
#define THREAD_100_HZ
#define THREAD_50_HZ
#define THREAD_25_HZ
#define THREAD_10_HZ
#define THREAD_01_HZ

#include "base_c_types.h"
#include "cglm/types.h"
#include "logs.h"
#include "settings.h"
#include "string.h"

#define UNUSED(__VALUE__) ((void)(__VALUE__))

#endif /*PROJECT_H*/
