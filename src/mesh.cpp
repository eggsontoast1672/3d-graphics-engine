#include "engine/mesh.hpp"

namespace rasp
{
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
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float[4]), (void*)sizeof(float[2]));
    }

    Mesh::Mesh()
    {
        m_vao = init_and_bind_vao();
        m_vbo = init_and_bind_vbo();
        m_ebo = init_and_bind_ebo();

        configure_layout();
    }

    Mesh::~Mesh()
    {
        glDeleteBuffers(1, &m_ebo);
        glDeleteBuffers(1, &m_vbo);
        glDeleteVertexArrays(1, &m_vao);
    }
}
