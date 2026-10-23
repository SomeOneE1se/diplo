#ifndef TEXTURE_H
#define TEXTURE_H

#include "project.h"

typedef struct STexture
{
    TUInt        id;
    TInt         width;
    TInt         height;
    TInt         channels;
    const TChar *name;

} TTexture;

TTexture texture_load(
    const TChar *filename,
    const TChar *name
);

void texture_bind(TUInt id);

void texture_delete(TUInt *id);

#endif  // TEXTURE_H
