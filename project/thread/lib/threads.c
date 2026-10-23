#include "threads.h"

#define NS_PER_SEC 1000000000L

/**
 * @brief threads_mutexInit
 * @param m
 */
void threads_mutexInit(
    TMutex *m
)
{
#ifdef PLATFORM_WINDOWS
    InitializeCriticalSection(&m->mutex);
#else
    pthread_mutex_init(&m->mutex, NULL);
#endif
}

/**
 * @brief threads_mutexDelete
 * @param m
 */
void threads_mutexDelete(
    TMutex *m
)
{
#ifdef PLATFORM_WINDOWS
    DeleteCriticalSection(&m->mutex);
#else
    pthread_mutex_destroy(&m->mutex);
#endif
}

/**
 * @brief threads_mutexLock
 * @param m
 */
void threads_mutexLock(
    TMutex *m
)
{
#ifdef PLATFORM_WINDOWS
    EnterCriticalSection(&m->mutex);
#else
    pthread_mutex_lock(&m->mutex);
#endif
}

/**
 * @brief threads_mutexUnlock
 * @param m
 */
void threads_mutexUnlock(
    TMutex *m
)
{
#ifdef PLATFORM_WINDOWS
    LeaveCriticalSection(&m->mutex);
#else
    pthread_mutex_unlock(&m->mutex);
#endif
}

/**
 * @brief threads_condInit
 * @param c
 */
void threads_condInit(
    TCond *c
)
{
#ifdef PLATFORM_WINDOWS
    InitializeConditionVariable(&c->cond);
#else
    pthread_cond_init(&c->cond, NULL);
#endif
}

/**
 * @brief threads_condDelete
 * @param c
 */
void threads_condDelete(
    TCond *c
)
{
#ifdef PLATFORM_WINDOWS
    return;
#else
    pthread_cond_destroy(&c->cond);
#endif
}

/**
 * @brief threads_condWait
 * @param c
 * @param m
 */
void threads_condWait(
    TCond  *c,
    TMutex *m
)
{
#ifdef PLATFORM_WINDOWS
    SleepConditionVariableCS(&c->cond, &m->mutex, INFINITE);
#else
    pthread_cond_wait(&c->cond, &m->mutex);
#endif
}

/**
 * @brief threads_condSignal
 * @param c
 */
void threads_condSignal(
    TCond *c
)
{
#ifdef PLATFORM_WINDOWS
    WakeConditionVariable(&c->cond);
#else
    pthread_cond_signal(&c->cond);
#endif
}

TInt threads_createThread(
    TThread *thread,
#ifdef PLATFORM_WINDOWS
    DWORD WINAPI(func)(void *arg),
#else
    void *(*func)(void *),
#endif
    void *arg
)
{
#ifdef PLATFORM_WINDOWS
    thread->thread = CreateThread(NULL, 0, func, arg, 0, NULL);
    return 0;
#else
    TInt result = pthread_create(&thread->thread, NULL, func, arg);
    if (result != 0)
    {
        LOG_INFO("! thread create error %d\n", result);
    }
    return result;
#endif
}

/**
 * @brief threads_terminateThread
 * @param t
 */
void threads_terminateThread(
    TThread t
)
{
#ifdef PLATFORM_WINDOWS
    TerminateThread(t.thread, 0);
    CloseHandle(t.thread);
#else
    pthread_cancel(t.thread);
    pthread_join(t.thread, NULL);
#endif
}

/**
 * @brief threads_closeThread
 * @param t
 */
void threads_closeThread(
    TThread t
)
{
#ifdef PLATFORM_WINDOWS
    WaitForSingleObject(t.thread, INFINITE);
    CloseHandle(t.thread);
#else
    pthread_join(t.thread, NULL);
#endif
}

#ifdef PLATFORM_UNIX
/**
 * @brief timespec_add_ns
 * @param ts
 * @param ns
 */
void threads_timespecAddNs(
    struct timespec *ts,
    TLong            ns
)
{
    ts->tv_nsec += ns;
    while (NS_PER_SEC <= ts->tv_nsec)
    {
        ts->tv_nsec -= NS_PER_SEC;
        ts->tv_sec++;
    }
}
#endif

/**
 * @brief threads_work
 * @param task
 * @return
 */
TInt threads_work(
    TWorker *task
)
{
    threads_mutexLock(&task->mutex);

    while (!task->trigger && !task->terminate)
    {
        threads_condWait(&task->cond, &task->mutex);
    }

    if (task->terminate)
    {
        threads_mutexUnlock(&task->mutex);
        return 1;
    }

    task->trigger = FALSE;
    threads_mutexUnlock(&task->mutex);
    task->counter++;
    return 0;
}

/**
 * @brief threads_initWorker
 * @param task
 * @param name
 */
TInt threads_initWorker(
    TWorker     *task,
    const TChar *name,
#ifdef PLATFORM_WINDOWS
    DWORD WINAPI(func)(void *arg)
#else
    void *(*func)(void *)
#endif
)
{
    task->name      = name;
    task->terminate = FALSE;
    task->trigger   = FALSE;
    task->counter   = 1;
    threads_mutexInit(&task->mutex);
    threads_condInit(&task->cond);
    if (threads_createThread(&task->thread, func, task))
    {
        LOG_INFO("! Thread [%s] error\n", name);
        return FAILURE;
    }
    else
    {
        LOG_INFO("  Thread [%s] create\n", name);
        return SUCCESS;
    }
}

/**
 * @brief threads_terminateWorker
 * @param task
 */
void threads_terminateWorker(
    TWorker *task
)
{
    threads_mutexLock(&task->mutex);
    task->terminate = TRUE;
    threads_condSignal(&task->cond);
    threads_mutexUnlock(&task->mutex);

    threads_closeThread(task->thread);
    threads_mutexDelete(&task->mutex);
    threads_condDelete(&task->cond);
}
