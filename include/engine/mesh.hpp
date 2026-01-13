#pragma once

#include <GL/glew.h>

namespace rasp
{
    class Mesh
    {
    public:
        Mesh();
        ~Mesh();

    private:
        GLuint m_vao;
        GLuint m_vbo;
        GLuint m_ebo;
    };

    void engine_mesh_init(void);
    void engine_mesh_quit(void);
}
