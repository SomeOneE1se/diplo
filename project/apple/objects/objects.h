#ifndef OBJECTS_H
#define OBJECTS_H

#include "project.h"

typedef enum    EObjType
{
    OBJ_TRIANGLE,
    OBJ_POINT,

}               TObjType;

typedef struct  SObject
{
    TUInt       VBO, EBO, VAO;
    TUInt       EBOcount;
    TObjType    type;
    TUInt       shaderId, textureId;

    vec3        position;
    vec3        rotation;

    TFlag       visible;
}               TObject;

void objects_draw(
    TObject object
);

void objects_update(
    TObject object,
    mat4    model
);

void objects_delete(
    TObject *object
);

TObject objects_createLA(void);

TObject objects_createTargPoint(void);

TObject objects_createMap(void);

#endif // OBJECTS_H
