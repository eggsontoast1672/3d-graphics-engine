#include "engine/texture.h"

#include <GL/glew.h>

static GLuint s_texture_id = 0;

void engine_texture_init(void)
{
    glGenTextures(1, &s_texture_id);
    glBindTexture(GL_TEXTURE_2D, s_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void engine_texture_quit(void)
{
    glDeleteTextures(1, &s_texture_id);
}

void engine_texture_set_data(const Image *image)
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->data);
}
