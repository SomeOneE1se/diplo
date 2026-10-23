#include "input.h"
#include <math.h>
#include <string.h>

typedef struct SInput
{
    TFlag  keys[KEY_COUNT];
    TFlag  mButtons[MOUSE_BUTTON_COUNT];
    TUInt  keyFrames[KEY_COUNT];
    TUInt  mButtonFrames[MOUSE_BUTTON_COUNT];

    TUInt  current;
    TFloat deltaX;
    TFloat deltaY;
    TFloat x;
    TFloat y;
    TFloat scroll;

} TInput;

static TInput input;

/**
 * @brief input_cursorPosCallback
 * @param pWindow
 * @param xpos
 * @param ypos
 */
void input_cursorPosCallback(
    GLFWwindow *pWindow,
    TDouble     xpos,
    TDouble     ypos
)
{
    UNUSED(pWindow);

    input.deltaX += xpos - input.x;
    input.deltaY += ypos - input.y;

    input.x       = xpos;
    input.y       = ypos;
}

/**
 * @brief input_mouseButtonCallback
 * @param pWindow
 * @param button
 * @param action
 * @param mode
 */
void input_mouseButtonCallback(
    GLFWwindow *pWindow,
    TInt        button,
    TInt        action,
    TInt        mode
)
{
    UNUSED(pWindow);
    UNUSED(mode);

    if (action == PRESS)
    {
        input.mButtons[button]      = TRUE;
        input.mButtonFrames[button] = input.current;
    }
    else if (action == RELEASE)
    {
        input.mButtons[button]      = FALSE;
        input.mButtonFrames[button] = input.current;
    }
}

/**
 * @brief input_keyCallback
 * @param pWindow
 * @param key
 * @param scancode
 * @param action
 * @param mode
 */
void input_keyCallback(
    GLFWwindow *pWindow,
    TInt        key,
    TInt        scancode,
    TInt        action,
    TInt        mode
)
{
    UNUSED(pWindow);
    UNUSED(mode);
    UNUSED(scancode);

    if (action == PRESS)
    {
        input.keys[key]      = TRUE;
        input.keyFrames[key] = input.current;
    }
    else if (action == RELEASE)
    {
        input.keys[key]      = FALSE;
        input.keyFrames[key] = input.current;
    }
}

/**
 * @brief input_scrollCallback
 * @param pWindow
 * @param xoffset
 * @param yoffset
 */
void input_scrollCallback(
    GLFWwindow *pWindow,
    double      xoffset,
    double      yoffset
)
{
    UNUSED(pWindow);
    UNUSED(xoffset);

    LOG_INFO("scroll %f \t yoffset %f", input.scroll, yoffset);

    input.scroll += yoffset;

    if (fabs(input.scroll) < 0.01)
    {
        input.scroll = 0.0;
    }

    LOG_INFO("scroll %f \t yoffset %f\n", input.scroll, yoffset);
}

/**
 * @brief input_isPressed
 * @param keycode
 * @return
 */
TFlag input_isPressed(
    const TKeyCode keycode
)
{
    return input.keys[keycode];
}

/**
 * @brief input_isJPressed
 * @param keycode
 * @return
 */
TFlag input_isJPressed(
    const TKeyCode keycode
)
{
    return input.keys[keycode] && input.keyFrames[keycode] == input.current;
}

/**
 * @brief input_isClicked
 * @param button
 * @return
 */
TFlag input_isClicked(
    const TMouseButton button
)
{
    return input.mButtons[button];
}

/**
 * @brief input_isJClicked
 * @param button
 * @return
 */
TFlag input_isJClicked(
    const TMouseButton button
)
{
    return input.mButtons[button] && input.mButtonFrames[button] == input.current;
}

/**
 * @brief input_getCursorX
 * @return
 */
TFloat input_getCursorX(
    void
)
{
    return input.x;
}

/**
 * @brief input_getCursorY
 * @return
 */
TFloat input_getCursorY(
    void
)
{
    return input.y;
}

/**
 * @brief input_getScroll
 * @return
 */
TFloat input_getScroll(
    void
)
{
    return input.scroll;
}

/**
 * @brief input_onUpdate
 */
void input_onUpdate(
    void
)
{
    ++input.current;
    input.deltaX = 0.0f;
    input.deltaY = 0.0f;
}

/**
 * @brief input_initialize
 * @return
 */
TInt input_initialize(
    void
)
{
    memset(&input, 0, sizeof(TInput));
    return SUCCESS;
}

/**
 * @brief input_terminate
 */
void input_terminate(
    void
)
{
}
