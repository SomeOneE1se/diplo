#include "texture.h"
#include "glad/glad.h"
#include "support/glSupport.h"

#define STB_IMAGE_IMPLEMENTATION
#include "support/stb_image.h"

/**
 * @brief texture_load
 * @param filename
 * @param name
 * @return
 */
TTexture texture_load(
    const TChar *filename,
    const TChar *name
)
{
    TTexture texture = {0};

    texture.name     = name;

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    stbi_set_flip_vertically_on_load(TRUE);
    TUChar *data = stbi_load(filename, &texture.width, &texture.height, &texture.channels, 0);
    if (data)
    {
        LOG_INFO("\nalfacha - %d\n", texture.channels);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            chanellsToGLenum(texture.channels),
            texture.width,
            texture.height,
            0,
            chanellsToGLenum(texture.channels),
            GL_UNSIGNED_BYTE,
            data
        );
        glGenerateMipmap(GL_TEXTURE_2D);

        LOG_INFO("  Load texture [%s] success\n", name);
    }
    else
    {
        LOG_INFO("! Load texture [%s] error\n", name);
    }
    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

/**
 * @brief texture_bind
 * @param id
 */
void texture_bind(
    TUInt id
)
{
    glBindTexture(GL_TEXTURE_2D, id);
}

/**
 * @brief texture_delete
 * @param id
 */
void texture_delete(
    TUInt *id
)
{
    glDeleteTextures(1, id);
}
