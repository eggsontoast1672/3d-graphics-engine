#include "engine/shader.hpp"

#include <stdexcept>
#include <string>

const char* const vertex_source =
    "#version 330 core\n"
    "layout (location = 0) in vec2 position;\n"
    "layout (location = 1) in vec2 tex_coord;\n"
    "out vec2 v_tex_coord;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(position, 0.0f, 1.0f);\n"
    "   v_tex_coord = tex_coord;\n"
    "}\n";

const char* const fragment_source =
    "#version 330 core\n"
    "in vec2 v_tex_coord;\n"
    "out vec4 f_color;\n"
    "uniform sampler2D u_texture;\n"
    "void main()\n"
    "{\n"
    "   f_color = texture(u_texture, v_tex_coord);\n"
    "}\n";

static void check_compile_errors(GLuint shader)
{
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status == 0)
    {
        GLint info_log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
        std::string info_log(static_cast<std::size_t>(info_log_length), '\0');
        glGetShaderInfoLog(shader, info_log.size(), nullptr, info_log.data());

        throw std::runtime_error(info_log);
    }
}

/// Create a shader object.
static GLuint create_shader(GLenum type, const char* source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    check_compile_errors(shader);

    return shader;
}

ShaderProgram::ShaderProgram(const char* vertex_source, const char* fragment_source)
{
    GLuint vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_source);
    GLuint fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_source);

    m_id = glCreateProgram();
    glAttachShader(m_id, vertex_shader);
    glAttachShader(m_id, fragment_shader);
    glLinkProgram(m_id);

    check_link_errors();
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_id);
}

void ShaderProgram::check_link_errors() const
{
    GLint status;
    glGetProgramiv(m_id, GL_LINK_STATUS, &status);

    if (status == 0)
    {
        GLint info_log_length;
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &info_log_length);
        std::string info_log(static_cast<std::size_t>(info_log_length), '\0');
        glGetProgramInfoLog(m_id, info_log.size(), nullptr, info_log.data());

        throw std::runtime_error(info_log);
    }
}
