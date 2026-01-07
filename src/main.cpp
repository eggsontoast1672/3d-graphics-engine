#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

constexpr float vertices[] = {
    -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f};

constexpr unsigned int indices[] = {0, 1, 2, 1, 2, 3};

constexpr const char *vertex_source = R"glsl(#version 330 core

layout (location = 0) in vec2 position;

void main()
{
    gl_Position = vec4(position, 0.0f, 1.0f);
}
)glsl";

constexpr const char *fragment_source = R"glsl(#version 330 core

out vec4 f_color;

void main()
{
    f_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
)glsl";

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "3D Graphics Engine", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return 1;
    }

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height)
                                   { glViewport(0, 0, width, height); });

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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float[2]), 0);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vs, 1, &vertex_source, nullptr);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fs, 1, &fragment_source, nullptr);
    glCompileShader(fs);

    GLuint program = glCreateProgram();

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glUseProgram(program);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(program);
    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    glfwTerminate();
}
