#include "logic.h"
#include "graphics/renderer.h"
#include "support/deltaTimer.h"
#include "window/camera.h"
#include "window/input.h"
#include "window/window.h"

#include "cglm/cglm.h"
#include "glad/glad.h"

typedef enum EObjMode
{
    OBJ_IDLE,
    OBJ_MOVE

} TObjMode;

typedef struct SNavLogic
{
    vec3     velocity;

    TObjMode mode;

    float    maxSpeed;
    float    accel;
    float    turnRate;

} TNavLogic;

static TNavLogic logic;

/**
 * @brief logic_screenToWorld
 * @param worldPos
 */
static void logic_screenToWorld(
    vec3 worldPos
)
{
    vec4 viewport = {0.0f, 0.0f, (TFloat)window_getWidth(), (TFloat)window_getHeight()};

    mat4 proj, view, vp;
    camera_getProjection(proj);
    camera_getView(view);
    glm_mat4_mul(proj, view, vp);

    vec3 screenPos = {
        input_getCursorX(),
        (TFloat)window_getHeight() -
            input_getCursorY(),  // перекрутил, т.к. GLFW дает сверху вниз
        0.0f
    };

    glm_unproject(screenPos, vp, viewport, worldPos);
}

/**
 * @brief wrap_pi
 * @param a
 * @return
 */
static TFloat wrap_pi(
    TFloat a
)
{
    while (a > (TFloat)M_PI)
    {
        a -= 2.f * (TFloat)M_PI;
    }
    while (a < -(TFloat)M_PI)
    {
        a += 2.f * (TFloat)M_PI;
    }
    return a;
}

/**
 * @brief plane_steer_to_target
 * @param dt
 * @return
 */
static TInt plane_steer_to_target(
    TObject *plane,
    TObject *trg,
    TFloat   dt
)
{
    logic.maxSpeed = 12.0f;
    logic.accel    = 3.0f;
    logic.turnRate = 3.0f;

    vec3 to_target;
    glm_vec3_sub(trg->position, plane->position, to_target);

    float dist  = glm_vec3_norm(to_target);
    float speed = glm_vec3_norm(logic.velocity);

    vec3  dir   = {cosf(plane->rotation[K]), sinf(plane->rotation[K]), 0.0f};
    glm_vec3_scale(to_target, 1.f / dist, dir);

    float brake_dist    = (speed * speed) / (2.f * logic.accel);
    float desired_speed = (dist <= brake_dist) ? sqrtf(2.f * logic.accel * dist) : logic.maxSpeed;
    if (desired_speed > logic.maxSpeed)
    {
        desired_speed = logic.maxSpeed;
    }

    vec3 desired_vel;
    glm_vec3_scale(dir, desired_speed, desired_vel);

    vec3 dv;
    glm_vec3_sub(desired_vel, logic.velocity, dv);
    float dv_len = glm_vec3_norm(dv);

    float max_dv = logic.accel * dt;
    if (dv_len > max_dv)
    {
        glm_vec3_scale(dv, max_dv / dv_len, dv);
    }
    glm_vec3_add(logic.velocity, dv, logic.velocity);

    vec3 dp;
    glm_vec3_scale(logic.velocity, dt, dp);
    dp[Z] = 0.0f;
    glm_vec3_add(plane->position, dp, plane->position);

    float v_len = glm_vec3_norm(logic.velocity);
    if (v_len > 0.1f)
    {
        float desired_angle = atan2f(logic.velocity[Y], logic.velocity[X]);
        float da            = wrap_pi(desired_angle - plane->rotation[K]);
        float max_da        = logic.turnRate * dt;
        if (da > max_da)
        {
            da = max_da;
        }
        if (da < -max_da)
        {
            da = -max_da;
        }
        plane->rotation[K] = wrap_pi(plane->rotation[K] + da);
    }

    return (dist < 1.1f);
}

/**
 * @brief logic_inputProcess
 */
void logic_inputProcess(
    TObject *trg
)
{
    if (input_isPressed(KEY_ESCAPE) == TRUE)
    {
        window_setShouldClose(TRUE);
    }
    if (input_isClicked(MOUSE_BUTTON_RIGHT) == TRUE)
    {
        renderer_setClearColor(0.4f, 0.6f, 0.6f);
    }
    else
    {
        renderer_setClearColor(0.2f, 0.2f, 0.2f);
    }
    if (input_isJClicked(MOUSE_BUTTON_LEFT) == TRUE)
    {
        logic_screenToWorld(trg->position);
        trg->position[Z] = -0.5f;
        LOG_INFO("  target [%f\t%f]\n", trg->position[X], trg->position[Y]);
        trg->visible = TRUE;
        logic.mode   = OBJ_MOVE;
    }
}

/**
 * @brief logic_updateModel
 * @param model
 */
void logic_update(
    TObject *plane,
    TObject *trg
)
{
    float dt = deltaTimer_getDt();

    logic_inputProcess(trg);

    switch (logic.mode)
    {
    case OBJ_MOVE:
        if (plane_steer_to_target(plane, trg, dt))
        {
            glm_vec3_zero(logic.velocity);
            logic.mode   = OBJ_IDLE;
            trg->visible = FALSE;
        }
        break;
    case OBJ_IDLE: break;
    default      : break;
    }
}
