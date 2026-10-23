#ifndef INPUT_H
#define INPUT_H

#include "project.h"
#include "keys.h"

typedef struct GLFWwindow GLFWwindow;

void input_cursorPosCallback(
    GLFWwindow *pWindow,
    TDouble     xpos,
    TDouble     ypos
);

void input_mouseButtonCallback(
    GLFWwindow *pWindow,
    TInt        button,
    TInt        action,
    TInt        mode
);

void input_keyCallback(
    GLFWwindow *pWindow,
    TInt        key,
    TInt        scancode,
    TInt        action,
    TInt        mode
);

void input_scrollCallback(
    GLFWwindow *pWindow,
    double      xoffset,
    double      yoffset
);

TFlag input_isPressed(const TKeyCode keycode);

TFlag input_isJPressed(const TKeyCode keycode);

TFlag input_isClicked(const TMouseButton button);

TFlag input_isJClicked(const TMouseButton button);

TFloat input_getCursorX(void);

TFloat input_getCursorY(void);

TFloat input_getScroll(void);

void input_onUpdate(void);

TInt input_initialize(void);

void input_terminate(void);

#endif  // INPUT_H
