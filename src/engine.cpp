#include "engine/engine.hpp"

#include <GLFW/glfw3.h>

#include "engine/mesh.h"
#include "engine/shader.h"
#include "engine/texture.h"
#include "engine/window.h"
#include "engine/renderer/renderer.h"

static UpdateCallback s_update = NULL;

void engine_init(int width, int height, const char *title)
{
    engine_window_init(width, height, title);
    engine_mesh_init();
    engine_shader_init();
    engine_texture_init();

    renderer_init(width, height);
}

void engine_quit(void)
{
    renderer_quit();

    engine_texture_quit();
    engine_shader_quit();
    engine_mesh_quit();
    engine_window_quit();
}

void engine_set_update_callback(UpdateCallback callback)
{
    s_update = callback;
}

void engine_run(void)
{
    while (!engine_window_should_close())
    {
        engine_window_clear();

        if (s_update != NULL) s_update(NULL);

        engine_window_swap_buffers();
        engine_window_poll_events();
    }
}
