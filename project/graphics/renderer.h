#ifndef RENDERER_H
#define RENDERER_H

#include "project.h"

void renderer_clearGlErrors(void);

TFlag renderer_checkGlErrors(void);

void renderer_setClearColor(
    float r,
    float g,
    float b
);

void renderer_clear(void);

void renderer_setViewport(
    TUInt width,
    TUInt height
);

TInt renderer_initialize(void);

void renderer_terminate(void);

#endif  // RENDERER_H
