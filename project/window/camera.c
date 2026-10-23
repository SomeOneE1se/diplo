#include "camera.h"
#include "cglm/cglm.h"

typedef struct SCamera
{
    TUInt zoom;  // ????
    mat4  projection;
    mat4  view;
} TCamera;

static TCamera camera;

/**
 * @brief camera_getProjection
 * @param proj
 */
void camera_getProjection(
    mat4 proj
)
{
    memcpy(proj, camera.projection, sizeof(mat4));
}

/**
 * @brief camera_setProjection
 * @param proj
 */
void camera_setProjection(
    mat4 proj
)
{
    memcpy(camera.projection, proj, sizeof(mat4));
}

/**
 * @brief camera_getView
 * @param view
 */
void camera_getView(
    mat4 view
)
{
    memcpy(view, camera.view, sizeof(mat4));
}

/**
 * @brief camera_setView
 * @param view
 */
void camera_setView(
    mat4 view
)
{
    memcpy(camera.view, view, sizeof(mat4));
}

/**
 * @brief camera_initialize
 * @return
 */
TInt camera_initialize(
    void
)
{
    glm_ortho(ORTO_LEFT, ORTO_RIGHT, ORTO_BOT, ORTO_TOP, ORTO_NEAR, ORTO_FAR, camera.projection);

    glm_mat4_identity(camera.view);

    return SUCCESS;
}

/**
 * @brief camera_terminate
 */
void camera_terminate(
    void
)
{
}
