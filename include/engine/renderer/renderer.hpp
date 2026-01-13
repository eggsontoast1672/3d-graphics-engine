#pragma once

#include "engine/image.hpp"

namespace rasp
{
    class Renderer
    {
    public:
        Renderer(int width, int height);

        void clear(Color color);
        void fill_pixel(int x, int y, Color color);
        void fill_rect(int x1, int x2, int y1, int y2, Color color);

    private:
        Image m_framebuffer;
    };
}
