#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/engine.h"
#include "engine/renderer/renderer.h"

static void update_callback(void *user_data)
{
    renderer_clear(COLOR_BLACK);
    renderer_fill_pixel(100, 100, COLOR_RED);
    renderer_display();
}

int main()
{
    engine_init(800, 600, "3D Graphics Engine");
    engine_set_update_callback(update_callback);
    engine_run();
    engine_quit();

    // Image image;
    // image_create(256, 256, &image);
    // glBindTexture(GL_TEXTURE_2D, texture);
    // texture_set_data(&image);

    // while (!glfwWindowShouldClose(window))
    // {
    //     glClear(GL_COLOR_BUFFER_BIT);
    //     glUseProgram(program);
    //     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    //     glfwSwapBuffers(window);
    //     glfwPollEvents();
    // }
}
