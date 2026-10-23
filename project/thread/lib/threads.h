#ifndef THREADS_H
#define THREADS_H

#include "project.h"

#ifdef PLATFORM_WINDOWS
#    include "windows.h"
#    include "time.h"
#else
#    include "pthread.h"
#    include "time.h"
#endif

/******************************************************************************/

typedef struct SThread
{
#ifdef PLATFORM_WINDOWS
    HANDLE thread;
#else
    pthread_t thread;
#endif
} TThread;

typedef struct SMutex
{
#ifdef PLATFORM_WINDOWS
    CRITICAL_SECTION mutex;
#else
    pthread_mutex_t mutex;
#endif
} TMutex;

typedef struct SCond
{
#ifdef PLATFORM_WINDOWS
    CONDITION_VARIABLE cond;
#else
    pthread_cond_t cond;
#endif
} TCond;

typedef struct SWorker
{
    TThread      thread;
    TMutex       mutex;
    TCond        cond;
    TFlag        trigger;
    TFlag        terminate;
    TULong       counter;
    const TChar *name;

} TWorker;

void threads_mutexInit(TMutex *m);

void threads_mutexDelete(TMutex *m);

void threads_mutexLock(TMutex *m);

void threads_mutexUnlock(TMutex *m);

void threads_condInit(TCond *c);

void threads_condDelete(TCond *c);

void threads_condWait(
    TCond  *c,
    TMutex *m
);

void threads_condSignal(TCond *c);

TInt threads_createThread(
    TThread *thread,
#ifdef PLATFORM_WINDOWS
    DWORD WINAPI(func)(void *arg),
#else
    void *(*func)(void *arg),
#endif
    void *arg
);

void threads_terminateThread(TThread t);

void threads_closeThread(TThread t);

#ifdef PLATFORM_UNIX
void threads_timespecAddNs(
    struct timespec *ts,
    TLong            ns
);
#endif

TInt threads_work(TWorker *task);

TInt threads_initWorker(
    TWorker     *task,
    const TChar *name,
#ifdef PLATFORM_WINDOWS
    DWORD WINAPI(func)(LPVOID arg)
#else
    void *(*func)(void *arg)
#endif
);

void threads_terminateWorker(TWorker *task);

#endif  // THREADS_H
