#ifndef WINDOW_H
#define WINDOW_H

#include "project.h"

typedef struct GLFWwindow GLFWwindow;

TFloat window_getAspect(void);

TInt window_getWidth(void);

void window_setWidth(TInt width);

TInt window_getHeight(void);

void window_setHeight(TInt height);

struct GLFWwindow *window_getpWindowDesc(void);

TFlag window_isShouldClose(void);

void window_setShouldClose(TFlag flag);

void window_swapBuffers(void);

void window_windowSizeCallback(
    GLFWwindow *pWindow,
    TInt        width,
    TInt        height
);

TInt window_initialize(
    TInt  width,
    TInt  height,
    char *title
);

void window_terminate(void);

#endif  // WINDOW_H
