#pragma once

#include <GL/glew.h>

namespace rasp
{
    class Image;

    /// A buffer of RGB pixel data on the GPU.
    class Texture
    {
    public:
        /// Create a texture.
        Texture();

        /// Destroy a texture.
        ~Texture();

        /// Bind this texture.
        void bind() const;

        /// Unbind this texture.
        void unbind() const;

        /// Send new pixel data to the texture.
        void set_data(const Image& image) const;

    private:
        GLuint m_id;
    };
}
