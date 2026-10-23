#ifndef SHADER_H
#define SHADER_H

#include "project.h"

typedef struct SShader
{
    TUInt        id;
    const TChar *name;

} TShader;

TShader shader_createProgram(
    const char *vertexCodePath,
    const char *fragmentCodePath,
    const char *name
);

void shader_useProgram(TUInt id);

void shader_deleteProgram(TUInt id);

void shader_uniformMVP(
    TUInt id,
    mat4  projection,
    mat4  view,
    mat4  model
);

#endif  // SHADER_H
