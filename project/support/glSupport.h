#ifndef GLSUPPORT_H
#define GLSUPPORT_H

#include "project.h"

typedef enum EShaderDataType
{
    FLOAT,
    FLOAT2,
    FLOAT3,
    FLOAT4,
    INT,
    INT2,
    INT3,
    INT4
} TShaderDataType;

typedef enum EDrawUsage
{
    STATIC,
    DYNAMIC,
    STREAM
} TDrawUsage;

typedef enum EBufferType
{
    VERTEX,
    ELEMENTS
} TBufferType;

typedef enum EChannelType
{
    RGB  = 3,
    RGBA = 4
} TChannelType;

TUInt        targetToGLenum(const TBufferType target);

TUInt        chanellsToGLenum(const TChannelType channel);

TUInt        usageToGLenum(const TDrawUsage usage);

TUInt        shaderDataTypeSize(const TShaderDataType type);

TUInt        shaderDataTypeToComponentsCount(const TShaderDataType type);

TUInt        shaderDataTypeToComponentType(const TShaderDataType type);

const TChar *glSourceToString(const TUInt source);

const TChar *glTypeToString(const TUInt type);

#endif // GLSUPPORT_H
