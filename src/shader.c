#include "engine/shader.h"

static GLuint shader_create_internal(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    return shader;
}

GLuint shader_create(const char *vertex_source, const char *fragment_source)
{
    GLuint vertex_shader = shader_create_internal(GL_VERTEX_SHADER, vertex_source);
    GLuint fragment_shader = shader_create_internal(GL_FRAGMENT_SHADER, fragment_source);
    GLuint program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    return program;
}
