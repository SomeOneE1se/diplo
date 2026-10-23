#include "window/window.h"
#include "window/events.h"
#include "window/input.h"
#include "GLFW/glfw3.h"

static GLFWwindow *pWindow = NULL;
static TULong      counter = 0;

/**
 * @brief events_getUpdateCounter
 * @return
 */
TULong events_getUpdateCounter(
    void
)
{
    return counter;
}

/**
 * @brief errorCallback
 * @param error_code
 * @param description
 */
static void errorCallback(
    TInt         error_code,
    const TChar *description
)
{
    LOG_INFO("%d - %s\n", error_code, description);
}

/**
 * @brief events_pullEvents
 */
void events_pullEvents(
    void
)
{
    counter++;
    input_onUpdate();
    glfwPollEvents();
}

/**
 * @brief initialize
 * @return
 */
TInt events_initialize(
    void
)
{
    pWindow = window_getpWindowDesc();

    glfwSetErrorCallback(errorCallback);
    glfwSetWindowSizeCallback(/* */ pWindow, window_windowSizeCallback);
    glfwSetMouseButtonCallback(/**/ pWindow, input_mouseButtonCallback);
    glfwSetCursorPosCallback(/*  */ pWindow, input_cursorPosCallback);
    glfwSetKeyCallback(/*        */ pWindow, input_keyCallback);
    glfwSetScrollCallback(/*     */ pWindow, input_scrollCallback);

    return SUCCESS;
}

/**
 * @brief events_terminate
 */
void events_terminate(
    void
)
{
    pWindow = NULL;
}
