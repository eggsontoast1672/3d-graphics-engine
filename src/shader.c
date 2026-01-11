#include "engine/shader.h"

#include <GL/glew.h>

#define INFO_LOG_SIZE 1024

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

static ShaderResult create_shader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint status;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status == 0)
    {
        static char info_log[INFO_LOG_SIZE];

        glGetShaderInfoLog(shader, INFO_LOG_SIZE, NULL, info_log);

        ShaderResult result;

        result.succeeded = false;
        result.error.kind = SHADER_ERROR_COMPILE;
        result.error.shader_type = type;
        result.error.file_path = "<source>";
        result.error.info_log = info_log;

        return result;
    }

    ShaderResult result;

    result.succeeded = true;
    result.handle = shader;

    return result;
}

ShaderResult engine_shader_init(void)
{
    ShaderResult vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_source);
    ShaderResult fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_source);

    if (!vertex_shader.succeeded) return vertex_shader;
    if (!fragment_shader.succeeded) return fragment_shader;

    s_program_id = glCreateProgram();

    glAttachShader(s_program_id, vertex_shader.handle);
    glAttachShader(s_program_id, fragment_shader.handle);
    glLinkProgram(s_program_id);

    GLint status;

    glGetProgramiv(s_program_id, GL_LINK_STATUS, &status);

    if (status == 0)
    {
        static char info_log[INFO_LOG_SIZE];

        glGetProgramInfoLog(s_program_id, INFO_LOG_SIZE, NULL, info_log);

        ShaderResult result;

        result.succeeded = false;
        result.error.kind = SHADER_ERROR_LINK;
        result.error.file_path = "<source>";
        result.error.info_log = info_log;

        return result;
    }

    ShaderResult result;

    result.succeeded = true;
    result.handle = s_program_id;

    return result;
}

void engine_shader_quit(void)
{
    glDeleteProgram(s_program_id);
}
