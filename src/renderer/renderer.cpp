#include "engine/renderer/renderer.hpp"

#include "engine/image.hpp"
#include "engine/renderer/color.hpp"
#include "engine/texture.hpp"

namespace rasp
{
    Renderer::Renderer(int width, int height)
        : m_framebuffer(width, height)
    {
    }

    void Renderer::clear(Color color)
    {
        const int width = m_framebuffer.get_width();
        const int height = m_framebuffer.get_height();

        fill_rect(0, 0, width, height, color);
    }

    void Renderer::fill_pixel(int x, int y, Color color)
    {
        m_framebuffer.set_pixel(x, y, color);
    }

    void Renderer::fill_rect(int x1, int x2, int y1, int y2, Color color)
    {
        for (int y = y1; y < y2; y++)
        {
            for (int x = x1; x < x2; x++)
            {
                fill_pixel(x, y, color);
            }
        }
    }
}
