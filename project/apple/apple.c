#include "apple.h"
#include "logic.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/renderer.h"
#include "manager/manager.h"
#include "support/deltaTimer.h"
#include "thread/dispetcher.h"
#include "window/events.h"
#include "window/input.h"
#include "window/window.h"
#include "window/camera.h"
#include "apple/objects/objects.h"

#include "glad/glad.h"

/**
 * @brief apple_render
 */
void apple_render(
    void
)
{
    TObject plane  = objects_createLA();
    TObject target = objects_createTargPoint();
    TObject map    = objects_createMap();
    mat4    model, view, projection;

    camera_getProjection(projection);
    camera_getView(view);

    while (window_isShouldClose() == FALSE)
    {
        deltaTimer_tick();
        renderer_clear();

        logic_update(&plane, &target);

        objects_update(map, model);
        shader_uniformMVP(map.shaderId, projection, view, model);
        objects_draw(map);

        objects_update(target, model);
        shader_uniformMVP(target.shaderId, projection, view, model);
        objects_draw(target);

        objects_update(plane, model);
        shader_uniformMVP(plane.shaderId, projection, view, model);
        objects_draw(plane);

        events_pullEvents();
        window_swapBuffers();
    }

    objects_delete(&plane);
    objects_delete(&target);
    objects_delete(&map);
}

/**
 * @brief apple_initialize
 * @return
 */
TInt apple_initialize(
    void
)
{
#ifdef THREAD_INIT
    if (dispetcher_initialize())
    {
        return FAILURE;
    }
#endif
    if (window_initialize(WND_WIDTH, WND_HEIGHT, WND_NAME))
    {
        return FAILURE;
    }
    if (renderer_initialize())
    {
        return FAILURE;
    }
    if (input_initialize())
    {
        return FAILURE;
    }
    if (events_initialize())
    {
        return FAILURE;
    }
    if (camera_initialize())
    {
        return FAILURE;
    }
    if (deltaTimer_initialize())
    {
        return FAILURE;
    }
    if (manager_initialize())
    {
        return FAILURE;
    }

    return SUCCESS;
}

/**
 * @brief apple_terminate
 */
void apple_terminate(
    void
)
{
    manager_terminate();
    camera_terminate();
#ifdef THREAD_INIT
    dispetcher_terminate();
#endif
    events_terminate();
    renderer_terminate();
    window_terminate();
}
