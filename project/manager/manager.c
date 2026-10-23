#include "manager.h"
#include "graphics/shader.h"
#include "graphics/texture.h"

typedef struct SManager
{
    TShader  shader[SHADER_COUNT];
    TTexture texture[TEXTURE_COUNT];

} TManager;

static TManager manager = {0};

/**
 * @brief manager_getShaderId
 * @param shaderlist
 * @return
 */
TUInt manager_getShaderId(
    TShadersList shaderlist
)
{
    return manager.shader[shaderlist].id;
}

/**
 * @brief manager_getTextureId
 * @param texturelist
 * @return
 */
TUInt manager_getTextureId(
    TTexturesList texturelist
)
{
    return manager.texture[texturelist].id;
}

/**
 * @brief manager_initialize
 * @return
 */
TInt manager_initialize(
    void
)
{
    manager.shader[DEFAULT_SHADER] =
        shader_createProgram(DEFAULT_VERTEX, DEFAULT_FRAGMENT, "defaultShader");

    if (manager.shader[DEFAULT_SHADER].id == 0)
    {
        return FAILURE;
    }

    manager.shader[TEXTURE_SHADER] = shader_createProgram(
        "shaders/texture_vertex.glsl", "shaders/texture_fragment.glsl", "textureShader"
    );

    if (manager.shader[TEXTURE_SHADER].id == 0)
    {
        return FAILURE;
    }

    manager.texture[EARTH_TEXTURE] = texture_load("textures/Earth.png", "earth");

    if (manager.texture[EARTH_TEXTURE].id == 0)
    {
        return FAILURE;
    }

    return SUCCESS;
}

/**
 * @brief manager_terminate
 */
void manager_terminate(
    void
)
{
    texture_delete(&manager.texture[EARTH_TEXTURE].id);
    shader_deleteProgram(manager.shader[TEXTURE_SHADER].id);
    shader_deleteProgram(manager.shader[DEFAULT_SHADER].id);
}
