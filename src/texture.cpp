#include "engine/texture.hpp"

#include <GL/glew.h>

namespace rasp
{
    Texture::Texture()
    {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_id);

        // Unbind the texture so that it does not accidentally get used.
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::set_data(const Image& image) const
    {
        int width = image.get_width();
        int height = image.get_height();
        const std::uint8_t* pixels = image.get_pixels();

        bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        unbind();
    }
}
