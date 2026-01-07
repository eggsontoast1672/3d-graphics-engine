#include "engine/mesh.h"

#include <GL/glew.h>

typedef struct
{
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
} Mesh;

static Mesh s_quad_mesh = {0};

static GLuint init_and_bind_vao(void)
{
    GLuint vao;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    return vao;
}

static GLuint init_and_bind_vbo(void)
{
    static const float s_quad_vertices[] = {
        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f};

    GLuint vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof s_quad_vertices, s_quad_vertices, GL_STATIC_DRAW);

    return vbo;
}

static GLuint init_and_bind_ebo(void)
{
    static const unsigned int s_quad_indices[] = {0, 1, 2, 1, 2, 3};

    GLuint ebo;

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof s_quad_indices, s_quad_indices, GL_STATIC_DRAW);

    return ebo;
}

static void configure_layout(void)
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float[4]), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float[4]), (void *)sizeof(float[2]));
}

void mesh_quad_init(void)
{
    s_quad_mesh.vao = init_and_bind_vao();
    s_quad_mesh.vbo = init_and_bind_vbo();
    s_quad_mesh.ebo = init_and_bind_ebo();

    configure_layout();
}

void mesh_quad_deinit(void)
{
    glDeleteBuffers(1, &s_quad_mesh.ebo);
    glDeleteBuffers(1, &s_quad_mesh.vbo);
    glDeleteVertexArrays(1, &s_quad_mesh.vao);
}
