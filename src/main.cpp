#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "engine/engine.h"
#include "engine/renderer/renderer.h"

static void update_callback(void *user_data)
{
    renderer_clear(COLOR_BLACK);
    renderer_fill_rect(100, 100, 200, 200, COLOR_RED);
    renderer_display();
}

int main()
{
    engine_init(800, 600, "3D Graphics Engine");
    engine_set_update_callback(update_callback);
    engine_run();
    engine_quit();
}
