#include "deltaTimer.h"
#include "GLFW/glfw3.h"

typedef struct STimer
{
    TDouble now;
    TDouble last;
    TFloat  dt;
} TTimer;

static TTimer deltaTimer;

/**
 * @brief deltaTimer_getDt
 * @return
 */
TFloat deltaTimer_getDt(
    void
)
{
    return deltaTimer.dt;
}

/**
 * @brief deltaTimer_initialize
 * @return
 */
TInt deltaTimer_initialize(
    void
)
{
    deltaTimer.dt   = 0.0;
    deltaTimer.last = glfwGetTime();
    deltaTimer.now  = glfwGetTime();

    return SUCCESS;
}

/**
 * @brief deltaTimer_tick
 */
void deltaTimer_tick(
    void
)
{
    deltaTimer.now  = glfwGetTime();
    deltaTimer.dt   = (TFloat)(deltaTimer.now - deltaTimer.last);
    deltaTimer.last = deltaTimer.now;
    if (0.05f < deltaTimer.dt)
    {
        deltaTimer.dt = 0.05f;
    }
}
