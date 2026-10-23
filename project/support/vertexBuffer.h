#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "project.h"

typedef struct  SVertexBuffer
{
    TUInt       VBO;
    TUInt       verticesSize;
    TFloat     *vertices;
}               TVertexBuffer;

#endif // VERTEXBUFFER_H
