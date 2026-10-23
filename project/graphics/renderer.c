#include "renderer.h"
#include "window/window.h"
#include "glad/glad.h"
#include "support/glSupport.h"

static TFlag openGl_GLAD_init = FALSE;

/**
 * @brief renderer_clearGlErrors
 */
void renderer_clearGlErrors(
    void
)
{
#ifdef PRJ_DBG
    while (glGetError() != GL_NO_ERROR)
        ;
#endif
    return;
}

/**
 * @brief renderer_checkGlErrors
 */
TFlag renderer_checkGlErrors(
    void
)
{
#ifdef PRJ_DBG
    GLenum error = GL_NO_ERROR;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        LOG_INFO("!  openGl error %d\n", error);
        return FALSE;
    }
#endif
    return TRUE;
}

/**
 * @brief debugMessageCallback
 * @param source
 * @param type
 * @param id
 * @param severity
 * @param length
 * @param message
 * @param userParam
 */
static void debugMessageCallback(
    TUInt        source,
    TUInt        type,
    TUInt        id,
    TUInt        severity,
    TInt         length,
    const TChar *message,
    const void  *userParam
)
{
    UNUSED(length);
    UNUSED(userParam);

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        LOG_INFO(
            "! OpenGL Error: [%s : %s] %d): %s\n",
            glSourceToString(source),
            glTypeToString(type),
            id,
            message
        );
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        LOG_INFO(
            "! OpenGL Warning: [%s : %s] %d): %s\n",
            glSourceToString(source),
            glTypeToString(type),
            id,
            message
        );
        break;
    case GL_DEBUG_SEVERITY_LOW:
        LOG_INFO(
            "  OpenGL Info: [%s : %s] %d): %s\n",
            glSourceToString(source),
            glTypeToString(type),
            id,
            message
        );
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        LOG_INFO(
            "  OpenGL Notificaton: [%s : %s] %d): %s\n",
            glSourceToString(source),
            glTypeToString(type),
            id,
            message
        );
        break;
    default:
        LOG_INFO(
            "! OpenGL Error: [%s : %s] %d): %s\n",
            glSourceToString(source),
            glTypeToString(type),
            id,
            message
        );
    }
}

/**
 * @brief renderer_setClearColor
 * @param r
 * @param g
 * @param b
 * @param a
 */
void renderer_setClearColor(
    float r,
    float g,
    float b
)
{
    glClearColor(r, g, b, 1.0f);
}

/**
 * @brief renderer_clear
 */
void renderer_clear(
    void
)
{
    glClear(GL_COLOR_BUFFER_BIT);
}

/**
 * @brief renderer_setViewport
 * @param width
 * @param height
 */
void renderer_setViewport(
    TUInt width,
    TUInt height
)
{
    glViewport(0, 0, width, height);
}

/**
 * @brief renderer_initialize
 * @return
 */
TInt renderer_initialize(
    void
)
{
    if (openGl_GLAD_init == TRUE)
    {
        return SUCCESS;
    }

    if (!gladLoadGL())
    {
        LOG_INFO("! Failed to load GLAD\n");
    }
    else
    {
        openGl_GLAD_init = TRUE;
    }

    LOG_INFO("  OpenGL context initialized\n");

    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageControl(
        GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE
    );
    glDebugMessageCallback(debugMessageCallback, NULL);

    renderer_setViewport(window_getWidth(), window_getHeight());

    return SUCCESS;
}

/**
 * @brief renderer_terminate
 */
void renderer_terminate(
    void
)
{
}
