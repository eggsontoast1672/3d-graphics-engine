#include "engine/window.hpp"

#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace rasp
{
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    Window::Window(int width, int height, const char* title)
    {
        if (!glfwInit())
        {
            const char* description;
            glfwGetError(&description);
            throw std::runtime_error(description);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = std::unique_ptr<GLFWwindow, Deleter>(glfwCreateWindow(width, height, title, NULL, NULL));
        if (!m_window)
        {
            const char* description;
            glfwGetError(&description);
            glfwTerminate();
            throw std::runtime_error(description);
        }

        glfwSetFramebufferSizeCallback(m_window.get(), framebuffer_size_callback);
        glfwMakeContextCurrent(m_window.get());

        GLenum glew_result = glewInit();
        if (glew_result != GLEW_OK)
        {
            const GLubyte* bytes = glewGetErrorString(glew_result);
            const char* message = reinterpret_cast<const char*>(bytes);
            glfwTerminate();
            throw std::runtime_error(message);
        }
    }

    bool Window::should_close() const
    {
        glfwPollEvents();
        return glfwWindowShouldClose(m_window.get());
    }

    void Window::clear() const
    {
        /// There is an argument that this method should be static since it does
        /// not depend on the state of this window object, but having the method
        /// as non-static does guarantee that a window exists, and this a valid
        /// OpenGL context exists.
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::display() const
    {
        glfwSwapBuffers(m_window.get());
    }
}
