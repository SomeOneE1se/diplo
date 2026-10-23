#include "objects.h"
#include "cglm/cglm.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "manager/manager.h"
#include <glad/glad.h>
#include <math.h>

typedef struct SVertex
{
    TFloat X, Y, Z;
    TFloat R, G, B;

} TVertex;

typedef struct SVertex1
{
    TFloat X, Y, Z;
    TFloat U, V;

} TVertex1;

/**
 * @brief objects_draw
 * @param object
 */
void objects_draw(
    TObject object
)
{
    if (object.visible == FALSE)
    {
        return;
    }

    shader_useProgram(object.shaderId);
    texture_bind(object.textureId);

    glBindVertexArray(object.VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.EBO);
    switch (object.type)
    {
    case OBJ_TRIANGLE:
        glDrawElements(GL_TRIANGLES, object.EBOcount, GL_UNSIGNED_INT, 0);
        break;
    case OBJ_POINT:
        glPointSize(8.0f);
        glDrawElements(GL_POINTS, object.EBOcount, GL_UNSIGNED_INT, 0);
        break;
    default:
        break;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    shader_useProgram(0);
    texture_bind(0);
}

/**
 * @brief objects_delete
 * @param object
 */
void objects_delete(
    TObject *object
)
{
    glDeleteBuffers(1, &object->EBO);
    glDeleteBuffers(1, &object->VBO);
    glDeleteVertexArrays(1, &object->VAO);
    memset(object, 0, sizeof(TObject));
}

/**
 * @brief objects_update
 * @param object
 * @param model
 */
void objects_update(
    TObject object,
    mat4    model
)
{
    shader_useProgram(object.shaderId);
    glm_mat4_identity(model);
    glm_translate(model, object.position);
    glm_rotate(model, object.rotation[X], (vec3){1, 0, 0});
    glm_rotate(model, object.rotation[Y], (vec3){0, 1, 0});
    glm_rotate(model, object.rotation[Z], (vec3){0, 0, 1});
}

/**
 * @brief objects_createLA
 * @return
 */
TObject objects_createLA(
    void
)
{
    TObject object     = {0};

    // clang-format off
    TVertex  vertices[] = {
    //  X       Y       Z       R       G       B
    {   3.0f,   0.0f,   0.0f,   0.0f,   1.0f,   1.0f    },  // 0    top
    {  -2.0f,  -2.0f,   0.0f,   0.0f,   1.0f,   0.0f    },  // 1    left
    {  -2.0f,   2.0f,   0.0f,   0.0f,   1.0f,   0.0f    },  // 2    right
    {   0.0f,   0.0f,   0.0f,   1.0f,   0.0f,   0.0f    },  // 3    bot
    };

    TUInt indices[] = {
        0,  1,  3,
        0,  2,  3,
    };
    // clang-format on

    glGenVertexArrays(1, &object.VAO);
    glGenBuffers(1, &object.VBO);
    glGenBuffers(1, &object.EBO);
    glBindVertexArray(object.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, object.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    object.EBOcount = sizeof(indices) / sizeof(TUInt);
    object.type     = OBJ_TRIANGLE;
    object.visible  = TRUE;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(TFloat), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(TFloat), (void *)(3 * sizeof(TFloat))
    );
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    object.shaderId  = manager_getShaderId(DEFAULT_SHADER);
    object.textureId = 0;

    return object;
}

/**
 * @brief objects_createTargPoint
 * @return
 */
TObject objects_createTargPoint(
    void
)
{
    TObject object     = {0};

    // clang-format off
    TVertex  vertices[] = {
    //  X       Y       Z       R       G       B
    {   0.0f,   0.0f,   0.5f,   1.0f,   0.0f,   0.0f    }
    };

    TUInt indices[] = {
        0,
    };
    // clang-format on

    glGenVertexArrays(1, &object.VAO);
    glGenBuffers(1, &object.VBO);
    glGenBuffers(1, &object.EBO);
    glBindVertexArray(object.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, object.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    object.EBOcount = sizeof(indices) / sizeof(TUInt);
    object.type     = OBJ_POINT;
    object.visible  = FALSE;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(TFloat), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(TFloat), (void *)(3 * sizeof(TFloat))
    );
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    object.shaderId  = manager_getShaderId(DEFAULT_SHADER);
    object.textureId = 0;

    return object;
}

/**
 * @brief objects_createMap
 * @return
 */
TObject objects_createMap(
    void
)
{
    TObject object = {0};

    // clang-format off
    TVertex1  vertices[] = {
        //  X       Y       Z       U       V
        {  -180.0f, 90.0f,  0.0f,   0.0f,   1.0f    },  // top l
        {  -180.0f,-90.0f,  0.0f,   0.0f,   0.0f    },  // bot l
        {   180.0f, 90.0f,  0.0f,   1.0f,   1.0f    },  // top r
        {   180.0f,-90.0f,  0.0f,   1.0f,   0.0f    },  // bot r
    };
    
    TUInt indices[] = {
        0,  1,  2,
        3,  2,  1,  
    };
    // clang-format on

    glGenVertexArrays(1, &object.VAO);
    glGenBuffers(1, &object.VBO);
    glGenBuffers(1, &object.EBO);
    glBindVertexArray(object.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, object.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    object.EBOcount = sizeof(indices) / sizeof(TUInt);
    object.visible  = TRUE;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(TFloat), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        5 * sizeof(TFloat),
        (void *)(3 * sizeof(TFloat))
    );
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    object.shaderId    = manager_getShaderId(TEXTURE_SHADER);
    object.textureId   = manager_getTextureId(EARTH_TEXTURE);

    return object;
}
