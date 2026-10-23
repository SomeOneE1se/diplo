#include "dispetcher.h"
#include "lib/threads.h"
#include "workers.h"
#include "window/events.h"

#ifdef PLATFORM_WINDOWS
#    include "mmsystem.h"
#endif

#define PERIOD_NS 10000000L
#define PERIOD_MS 10

static TWorker task100 = {0};
static TWorker task50  = {0};
static TWorker task25  = {0};
static TWorker task10  = {0};
static TWorker task01  = {0};
static TThread dispetcherThread;

/**
 * @brief threadSignal
 * @param worker
 */
static void threadSignal(
    TWorker *worker
)
{
    threads_mutexLock(&worker->mutex);
    if (worker->trigger)
    {
        LOG_INFO("! [%s] is trigered! tick skip\n", worker->name);
    }
    worker->trigger = TRUE;
    threads_condSignal(&worker->cond);
    threads_mutexUnlock(&worker->mutex);
}

#ifdef PLATFORM_WINDOWS
DWORD WINAPI dispetcher(
    void *arg
)
#else
void *dispetcher(
    void *arg
)
#endif
{
    TULong tickCount = 0;

#ifdef PLATFORM_WINDOWS
    HANDLE        timer = CreateWaitableTimer(NULL, TRUE, NULL);
    LARGE_INTEGER time;
    time.QuadPart = -(PERIOD_MS * 10000LL);
    SetWaitableTimer(timer, &time, PERIOD_MS, NULL, NULL, 0);
#else
    struct timespec nextTime;
    clock_gettime(CLOCK_MONOTONIC, &nextTime);
#endif
    while (TRUE)
    {
#ifdef PLATFORM_WINDOWS
        WaitForSingleObject(timer, INFINITE);
#else
        threads_timespecAddNs(&nextTime, PERIOD_NS);
        while (clock_nanosleep(
                   CLOCK_MONOTONIC, TIMER_ABSTIME, &nextTime, NULL
               ) != 0)
            ;
#endif
        tickCount++;

#ifdef THREAD_100_HZ
        if (tickCount % 1 == 0)
        {
            threadSignal(&task100);
        }
#endif
#ifdef THREAD_50_HZ
        if (tickCount % 2 == 0)
        {
            threadSignal(&task50);
        }
#endif
#ifdef THREAD_25_HZ
        if (tickCount % 4 == 0)
        {
            threadSignal(&task25);
        }
#endif
#ifdef THREAD_10_HZ
        if (tickCount % 10 == 0)
        {
            threadSignal(&task10);
        }
#endif
#ifdef THREAD_01_HZ
        if (tickCount % 100 == 0)
        {
            threadSignal(&task01);
        }
#endif
#ifdef THREAD_COUNTERS_PRINT
        if (tickCount % 1000 == 0)
        {
            TULong renderUpdateCounter = events_getUpdateCounter();
            LOG_INFO(
                "\n- Threads counters:\t%ld \t%ld \t%ld \t%ld \t%ld \t| \t%ld "
                "\t%ld\n\n",
                task01.counter,
                task10.counter,
                task25.counter,
                task50.counter,
                task100.counter,
                tickCount,
                renderUpdateCounter
            );
        }
#endif
    }
#ifdef PLATFORM_WINDOWS
    CloseHandle(timer);
#endif
}

/**
 * @brief dispetcher_initialize
 * @return
 */
TInt dispetcher_initialize(
    void
)
{
#ifdef PLATFORM_WINDOWS
    timeBeginPeriod(1);
#endif

#ifdef THREAD_100_HZ
    if (threads_initWorker(&task100, "thread 100 Hz", worker100))
    {
        return FAILURE;
    }
#endif

#ifdef THREAD_50_HZ
    if (threads_initWorker(&task50, "thread  50 Hz", worker50))
    {
        return FAILURE;
    }
#endif

#ifdef THREAD_25_HZ
    if (threads_initWorker(&task25, "thread  25 Hz", worker25))
    {
        return FAILURE;
    }
#endif

#ifdef THREAD_10_HZ
    if (threads_initWorker(&task10, "thread  10 Hz", worker10))
    {
        return FAILURE;
    }
#endif

#ifdef THREAD_01_HZ
    if (threads_initWorker(&task01, "thread   1 Hz", worker01))
    {
        return FAILURE;
    }
#endif

    if (threads_createThread(&dispetcherThread, dispetcher, NULL))
    {
        return FAILURE;
    }

    LOG_INFO("  Dispetcher started succesfuly\n");
    return SUCCESS;
}

/**
 * @brief dispetcher_terminate
 */
void dispetcher_terminate(
    void
)
{
    threads_terminateThread(dispetcherThread);

#ifdef THREAD_100_HZ
    threads_terminateWorker(&task100);
#endif

#ifdef THREAD_50_HZ
    threads_terminateWorker(&task50);
#endif

#ifdef THREAD_25_HZ
    threads_terminateWorker(&task25);
#endif

#ifdef THREAD_10_HZ
    threads_terminateWorker(&task10);
#endif

#ifdef THREAD_01_HZ
    threads_terminateWorker(&task01);
#endif

#ifdef PLATFORM_WINDOWS
    timeEndPeriod(1);
#endif
}
