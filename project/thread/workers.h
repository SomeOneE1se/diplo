#ifndef WORKERS_H
#define WORKERS_H

#include "project.h"

#ifdef PLATFORM_WINDOWS
#    include "windows.h"
#endif

#ifdef PLATFORM_WINDOWS
typedef unsigned __LONG32 DWORD;

DWORD WINAPI worker100(void *arg);

DWORD WINAPI worker50(void *arg);

DWORD WINAPI worker25(void *arg);

DWORD WINAPI worker10(void *arg);

DWORD WINAPI worker01(void *arg);

#else

void *worker100(void *arg);

void *worker50(void *arg);

void *worker25(void *arg);

void *worker10(void *arg);

void *worker01(void *arg);

#endif

#endif  // WORKERS_H
