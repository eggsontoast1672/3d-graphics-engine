#pragma once

#include <stdbool.h>

#include <GL/glew.h>

typedef struct
{
    bool succeeded;

    union
    {
        GLuint handle;

        struct
        {
            enum
            {
                SHADER_ERROR_COMPILE,
                SHADER_ERROR_LINK,
            } kind;

            GLenum shader_type;
            const char *file_path;
            const char *info_log;
        } error;
    };
} ShaderResult;

ShaderResult engine_shader_init(void);
void engine_shader_quit(void);
