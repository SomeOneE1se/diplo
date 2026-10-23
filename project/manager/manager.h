#ifndef MANAGER_H
#define MANAGER_H

#include "project.h"

typedef enum EShadersList
{
    DEFAULT_SHADER,
    TEXTURE_SHADER,
    SHADER_COUNT
} TShadersList;

typedef enum ETexturesList
{
    EARTH_TEXTURE,
    TEXTURE_COUNT
} TTexturesList;

TUInt manager_getShaderId(TShadersList shaderlist);

TUInt manager_getTextureId(TTexturesList texturelist);

TInt manager_initialize(void);

void manager_terminate(void);

#endif // MANAGER_H
