#ifndef CAMERA_H
#define CAMERA_H

#include "project.h"

void camera_getProjection(mat4 proj);

void camera_setProjection(mat4 proj);

void camera_getView(mat4 view);

void camera_setView(mat4 view);

TInt camera_initialize(void);

void camera_terminate(void);

#endif  // CAMERA_H
