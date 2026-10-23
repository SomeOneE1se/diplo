#ifndef LOGS_H
#define LOGS_H

#include "stdio.h"

#ifndef PRJ_DBG
#    define LOG_INFO(...)
#    define LOG_HERE()
#else
#    define LOG_INFO(...) printf(__VA_ARGS__)
#    define LOG_HERE()    printf("  Here! %s - %d\n", __FILE__, __LINE__)
#endif

#endif  // LOGS_H
