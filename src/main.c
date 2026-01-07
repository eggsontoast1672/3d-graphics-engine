#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/image.h"
#include "engine/shader.h"
#include "engine/texture.h"

const float vertices[] = {
    -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f};

const unsigned int indices[] = {0, 1, 2, 1, 2, 3};

const char *const vertex_source =
    "#version 330 core\n"
    "layout (location = 0) in vec2 position;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(position, 0.0f, 1.0f);\n"
    "}\n";

const char *const fragment_source =
    "#version 330 core\n"
    "out vec4 f_color;\n"
    "void main()\n"
    "{\n"
    "   f_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n";

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void image_palette_test(const Image *image)
{
    for (size_t y = 0; y < image->height; y++)
    {
        for (size_t x = 0; x < image->width; x++)
        {
            uint8_t r = (uint8_t)((float)x / image->height * 255.0f);
            uint8_t g = (uint8_t)((float)y / image->height * 255.0f);
            uint8_t b = 0.0f;

            image_set_pixel(image, x, y, r, g, b);
        }
    }
}

int main()
{
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "3D Graphics Engine", NULL, NULL);
    if (window == NULL)
    {
        fprintf(stderr, "Failed to create window\n");
        glfwTerminate();
        return 1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwMakeContextCurrent(window);
    glewInit();

    GLuint vao;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    GLuint ibo;

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float[4]), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float[4]), (void *)sizeof(float[2]));

    GLuint program = shader_create(vertex_source, fragment_source);
    GLuint texture = texture_create();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteTextures(1, &texture);
    glDeleteProgram(program);
    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    glfwTerminate();
}
