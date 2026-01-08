#include "engine/shader.h"

#include <GL/glew.h>

const char *const vertex_source =
    "#version 330 core\n"
    "layout (location = 0) in vec2 position;\n"
    "layout (location = 1) in vec2 tex_coord;\n"
    "out vec2 v_tex_coord;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(position, 0.0f, 1.0f);\n"
    "   v_tex_coord = tex_coord;\n"
    "}\n";

const char *const fragment_source =
    "#version 330 core\n"
    "in vec2 v_tex_coord;\n"
    "out vec4 f_color;\n"
    "uniform sampler2D u_texture;\n"
    "void main()\n"
    "{\n"
    "   f_color = texture(u_texture, v_tex_coord);\n"
    "}\n";

static GLuint s_program_id = 0;

static GLuint create_shader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    return shader;
}

bool engine_shader_init(void)
{
    GLuint vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_source);
    GLuint fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_source);

    s_program_id = glCreateProgram();

    glAttachShader(s_program_id, vertex_shader);
    glAttachShader(s_program_id, fragment_shader);
    glLinkProgram(s_program_id);

    return true;
}

void engine_shader_quit(void)
{
    glDeleteProgram(s_program_id);
}
