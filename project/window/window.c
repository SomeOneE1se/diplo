#include "window/window.h"
#include "GLFW/glfw3.h"
#include "graphics/renderer.h"

static TFlag openGL_GLFW_Init = FALSE;

typedef struct SWindow
{
    struct GLFWwindow *pWindow;  //!< указатель на дескриптор окна
    TInt               width;    //!< ширина окна
    TInt               height;   //!< высота окна
    TFloat             aspect;

} TWindow;

/**
 * @brief window - синглтон окна приложения
 */
static TWindow window;

/**
 * @brief window_getAspect
 * @return
 */
TFloat window_getAspect(
    void
)
{
    return window.aspect;
}

/**
 * @brief window_getWidth
 * @return
 */
TInt window_getWidth(
    void
)
{
    return window.width;
}

/**
 * @brief window_setWidth
 * @param width
 */
void window_setWidth(
    TInt width
)
{
    window.width = width;
}

/**
 * @brief window_getHeight
 * @return
 */
TInt window_getHeight(
    void
)
{
    return window.height;
}

/**
 * @brief window_setHeight
 * @param height
 */
void window_setHeight(
    TInt height
)
{
    window.height = height;
}

/**
 * @brief window_getpWindowDesc
 * @return
 */
GLFWwindow *window_getpWindowDesc(
    void
)
{
    return window.pWindow;
}

/**
 * @brief window_isShouldClose
 * @return
 */
TFlag window_isShouldClose(
    void
)
{
    return glfwWindowShouldClose(window.pWindow);
}

/**
 * @brief window_setShouldClose
 * @param flag
 */
void window_setShouldClose(
    TFlag flag
)
{
    glfwSetWindowShouldClose(window.pWindow, flag);
}

/**
 * @brief window_swapBuffers
 */
void window_swapBuffers(
    void
)
{
    glfwSwapBuffers(window.pWindow);
}

/**
 * @brief window_windowSizeCallback
 * @param pWindow
 * @param width
 * @param height
 */
void window_windowSizeCallback(
    GLFWwindow *pWindow,
    TInt        width,
    TInt        height
)
{
    UNUSED(pWindow);
    renderer_setViewport(width, height);
    window.width  = width;
    window.height = height;
    window.aspect = (float)width / (float)height;
}

/**
 * @brief window_initialize
 * @param width
 * @param height
 * @param title
 * @return
 */
TInt window_initialize(
    TInt  width,
    TInt  height,
    char *title
)
{
    if (openGL_GLFW_Init == TRUE)
    {
        return SUCCESS;
    }

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPEN_GL_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPEN_GL_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, WND_RESIZABLE);

    GLFWmonitor       *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *vidmode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, /*    */ vidmode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, /*  */ vidmode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, /*   */ vidmode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, /**/ vidmode->refreshRate);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

    window.pWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window.pWindow == NULL)
    {
        glfwTerminate();
        LOG_INFO("! Failed to create GLFW Window\n");
        return FAILURE;
    }
    else
    {
        openGL_GLFW_Init = TRUE;
        LOG_INFO("  GLFW window initialized\n");
    }

    window.height = height;
    window.width  = width;
    window.aspect = (float)width / (float)height;

    glfwMakeContextCurrent(window.pWindow);
    glfwSwapInterval(WND_VERT_SYNC);

    return SUCCESS;
}

/**
 * @brief window_terminate
 */
void window_terminate(
    void
)
{
    glfwDestroyWindow(window.pWindow);
    window.pWindow = NULL;
    LOG_INFO("  GLFW window terminate\n");
    glfwTerminate();
}
