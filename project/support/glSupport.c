#include "glSupport.h"
#include <glad/glad.h>

TUInt targetToGLenum(
    const TBufferType target
)
{
    switch (target)
    {
    case VERTEX  : return GL_ARRAY_BUFFER;
    case ELEMENTS: return GL_ELEMENT_ARRAY_BUFFER;
    }
    return GL_ARRAY_BUFFER;
}

TUInt chanellsToGLenum(
    const TChannelType channel
)
{
    switch (channel)
    {
    case RGB:
        return GL_RGB;
    case RGBA:
        return GL_RGBA;
    }
    return GL_RGB;
}

/**
 * @brief usageToGLenum
 * @param usage
 * @return
 */
TUInt usageToGLenum(
    const TDrawUsage usage
)
{
    switch (usage)
    {
    case STATIC : return GL_STATIC_DRAW;
    case DYNAMIC: return GL_DYNAMIC_DRAW;
    case STREAM : return GL_STREAM_DRAW;
    }
    return GL_STREAM_DRAW;
}

/**
 * @brief shaderDataTypeSize
 * @param type
 * @return
 */
TUInt shaderDataTypeSize(
    const TShaderDataType type
)
{
    switch (type)
    {
    case FLOAT:
    case FLOAT2:
    case FLOAT3:
    case FLOAT4: return sizeof(TFloat) * shaderDataTypeToComponentsCount(type);

    case INT   :
    case INT2  :
    case INT3  :
    case INT4  : return sizeof(TInt) * shaderDataTypeToComponentsCount(type);
    }

    return 0;
}

/**
 * @brief shaderDataTypeToComponentsCount
 * @param type
 * @return
 */
TUInt shaderDataTypeToComponentsCount(
    const TShaderDataType type
)
{
    switch (type)
    {
    case FLOAT:
    case INT   : return 1;

    case FLOAT2:
    case INT2  : return 2;

    case FLOAT3:
    case INT3  : return 3;

    case FLOAT4:
    case INT4  : return 4;
    }

    return 0;
}

/**
 * @brief shaderDataTypeToComponentType
 * @param type
 * @return
 */
TUInt shaderDataTypeToComponentType(
    const TShaderDataType type
)
{
    switch (type)
    {
    case FLOAT:
    case FLOAT2:
    case FLOAT3:
    case FLOAT4: return GL_FLOAT;

    case INT   :
    case INT2  :
    case INT3  :
    case INT4  : return GL_INT;
    }

    return GL_FLOAT;
}

/**
 * @brief glSourceToString
 * @param source
 * @return
 */
const TChar *glSourceToString(
    const TUInt source
)
{
    switch (source)
    {
    case GL_DEBUG_SOURCE_API            : return "DEBUG_SOURCE_API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM  : return "DEBUG_SOURCE_WINDOW_SYSTEM";
    case GL_DEBUG_SOURCE_SHADER_COMPILER: return "GL_DEBUG_SOURCE_SHADER_COMPILER";
    case GL_DEBUG_SOURCE_THIRD_PARTY    : return "DEBUG_SOURCE_THIRD_PARTY";
    case GL_DEBUG_SOURCE_APPLICATION    : return "DEBUG_SOURCE_APPLICATION";
    case GL_DEBUG_SOURCE_OTHER          : return "DEBUG_SOURCE_OTHER";

    default                             : return "UNKNOWN_DEBUG_SOURCE";
    }
}

/**
 * @brief glTypeToString
 * @param type
 * @return
 */
const TChar *glTypeToString(
    const TUInt type
)
{
    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR              : return "DEBUG_TYPE_ERROR";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEBUG_TYPE_DEPRECATED_BEHAVIOR";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR : return "DEBUG_TYPE_UNDEFINED_BEHAVIOR";
    case GL_DEBUG_TYPE_PORTABILITY        : return "DEBUG_TYPE_PORTABILITY";
    case GL_DEBUG_TYPE_PERFORMANCE        : return "DEBUG_TYPE_PERFORMANCE";
    case GL_DEBUG_TYPE_MARKER             : return "DEBUG_TYPE_MARKER";
    case GL_DEBUG_TYPE_PUSH_GROUP         : return "DEBUG_TYPE_PUSH_GROUP";
    case GL_DEBUG_TYPE_POP_GROUP          : return "DEBUG_TYPE_POP_GROUP";
    case GL_DEBUG_TYPE_OTHER              : return "DEBUG_TYPE_OTHER";

    default                               : return "UNKNOWN_DEBUG_TYPE";
    }
}
