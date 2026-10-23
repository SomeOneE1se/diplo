#include "workers.h"
#include "lib/threads.h"

#ifdef PLATFORM_WINDOWS
DWORD WINAPI worker50(
    void *arg
)
#else
void *worker50(
    void *arg
)
#endif
{
    TWorker *task = (TWorker *)arg;

    while (TRUE)
    {
        if (threads_work(task))
        {
            break;
        }

        // here
    }

    LOG_INFO("  thread [%s] end\n", task->name);
    return 0;
}
