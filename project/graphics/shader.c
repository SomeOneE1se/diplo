#include "shader.h"
#include "files.h"
#include "glad/glad.h"

#define SHADER_FILE_BUFFER 1024

/**
 * @brief createShader
 * @param source
 * @param type
 * @return
 */
static GLuint createShader(
    const char *source,
    GLenum      type
)
{
    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(id, 1024, NULL, infoLog);
        LOG_INFO("! Shader compile time error:\n%s\n", infoLog);
    }
    else
    {
        if (type == GL_VERTEX_SHADER)
        {
            LOG_INFO("  Vertex Shader compile success\n");
        }
        else if (type == GL_FRAGMENT_SHADER)
        {
            LOG_INFO("  Fragment Shader compile success\n");
        }
        else
        {
            LOG_INFO("  Shader compile success\n");
        }
    }

    return id;
}

/**
 * @brief shader_createShaderProgram
 * @param vertexCodePath
 * @param fragmentCodePath
 * @return
 */
TShader shader_createProgram(
    const char *vertexCodePath,
    const char *fragmentCodePath,
    const char *name
)
{
    TShader shader                        = {0};

    shader.name                           = name;

    char vertexCode[SHADER_FILE_BUFFER]   = {0};
    char fragmentCode[SHADER_FILE_BUFFER] = {0};

    file_getFileContent(vertexCodePath, "rb", SHADER_FILE_BUFFER, vertexCode);
    file_getFileContent(fragmentCodePath, "rb", SHADER_FILE_BUFFER, fragmentCode);

    GLuint vertex   = createShader(vertexCode, GL_VERTEX_SHADER);
    GLuint fragment = createShader(fragmentCode, GL_FRAGMENT_SHADER);

    shader.id       = glCreateProgram();
    glAttachShader(shader.id, vertex);
    glAttachShader(shader.id, fragment);
    glLinkProgram(shader.id);

    GLint success;
    glGetProgramiv(shader.id, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(shader.id, 512, NULL, infoLog);

        glDeleteProgram(shader.id);

        LOG_INFO("! Shader program [%s] linking failed:\n%s\n", name, infoLog);
    }
    else
    {
        LOG_INFO("  Shader program [%s] linking success\n", name);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return shader;
}

/**
 * @brief shader_useProgram
 * @param id
 */
void shader_useProgram(
    TUInt id
)
{
    glUseProgram(id);
}

/**
 * @brief shader_deleteProgram
 * @param id
 */
void shader_deleteProgram(
    TUInt id
)
{
    glDeleteProgram(id);
}

/**
 * @brief shader_uniformMVP
 * @param id
 * @param projection
 * @param view
 * @param model
 */

void shader_uniformMVP(
    TUInt id,
    mat4  projection,
    mat4  view,
    mat4  model
)
{
    glUniformMatrix4fv(glGetUniformLocation(id, "model"), 1, GL_FALSE, (TFloat *)model);
    glUniformMatrix4fv(glGetUniformLocation(id, "view"), 1, GL_FALSE, (TFloat *)view);
    glUniformMatrix4fv(glGetUniformLocation(id, "projection"), 1, GL_FALSE, (TFloat *)projection);
}
