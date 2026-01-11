#include "engine/window.h"

#include <stdio.h>

#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

static GLFWwindow *s_window = NULL;

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

bool engine_window_init(int width, int height, const char *title)
{
    if (!glfwInit())
    {
        const char *description;
        glfwGetError(&description);
        fprintf(stderr, "Failed to initialize windowing system: %s\n", description);
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    s_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (s_window == NULL)
    {
        const char *description;
        glfwGetError(&description);
        fprintf(stderr, "Failed to create window: %s\n", description);
        glfwTerminate();
        return false;
    }

    glfwSetFramebufferSizeCallback(s_window, framebuffer_size_callback);
    glfwMakeContextCurrent(s_window);

    GLenum glew_result = glewInit();
    if (glew_result != GLEW_OK)
    {
        const GLubyte *error_string = glewGetErrorString(glew_result);
        fprintf(stderr, "Failed to initialize OpenGL: %s\n", error_string);
        glfwTerminate();
        return false;
    }

    return true;
}

void engine_window_quit(void)
{
    glfwTerminate();
}

bool engine_window_should_close(void)
{
    return glfwWindowShouldClose(s_window);
}

void engine_window_clear(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void engine_window_swap_buffers(void)
{
    glfwSwapBuffers(s_window);
}

void engine_window_poll_events(void)
{
    glfwPollEvents();
}
