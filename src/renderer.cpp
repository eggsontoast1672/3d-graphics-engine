#include "raspberry/renderer.hpp"

#include <cstdlib>
#include <cstring>
#include <utility>

namespace rasp
{
    Renderer::Renderer(const char* title, u16 width, u16 height)
        : m_logical_width(width),
          m_logical_height(height),
          m_frame_buffer(static_cast<decltype(m_frame_buffer)::size_type>(width * height * 3))
    {
        SDL_Init(SDL_INIT_VIDEO);

        m_window = SDL_CreateWindow(title, width * 4, height * 4, 0);
        m_renderer = SDL_CreateRenderer(m_window, nullptr);
        m_texture = SDL_CreateTexture(
            m_renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING,
            width, height);

        SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);
    }

    Renderer::~Renderer()
    {
        SDL_DestroyTexture(m_texture);
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
    }

    UVec2 Renderer::canonocalize(Vec4 vertex) const
    {
        const Vec4 homogenized = vertex / vertex.w;
        const Vec2
    }

    void Renderer::fill_pixel(u16 x, u16 y, Color color)
    {
        const std::size_t index = (y * m_logical_width + x) * 3;

        m_frame_buffer.at(index) = color.r;
        m_frame_buffer.at(index + 1) = color.g;
        m_frame_buffer.at(index + 2) = color.b;
    }

    void Renderer::fill_rect(u16 x0, u16 y0, u16 x1, u16 y1, Color color)
    {
        for (u16 y = y0; y <= y1; y++)
        {
            for (u16 x = x0; x <= x1; x++)
            {
                fill_pixel(x, y, color);
            }
        }
    }

    void Renderer::draw_horizontal_line(UVec2 p1, UVec2 p2, Color color)
    {
        if (p1.x > p2.x) std::swap(p1, p2);

        const i32 dx = p2.x - p1.x;
        i32 dy = p2.y - p1.y;
        const i32 dir = dy < 0 ? -1 : 1;
        dy *= dir;

        i32 y = p1.y;
        i32 d = 2 * dy - dx;

        for (i32 x = p1.x; x <= p2.x; x++)
        {
            fill_pixel(x, y, color);

            if (d >= 0)
            {
                y += dir;
                d -= 2 * dx;
            }

            d += 2 * dy;
        }
    }

    void Renderer::draw_vertical_line(UVec2 p1, UVec2 p2, Color color)
    {
        if (p1.y > p2.y) std::swap(p1, p2);

        i32 dx = p2.x - p1.x;
        const i32 dy = p2.y - p1.y;
        const i32 dir = dx < 0 ? -1 : 1;
        dx *= dir;

        i32 x = p1.x;
        i32 d = 2 * dx - dy;

        for (i32 y = p1.y; y <= p2.y; y++)
        {
            fill_pixel(x, y, color);

            if (d >= 0)
            {
                x += dir;
                d -= 2 * dy;
            }

            d += 2 * dx;
        }
    }

    void Renderer::draw_line(Vec4 p1, Vec4 p2, Color color)
    {
        const UVec2 p1_normal = canonocalize(p1);
        const UVec2 p2_normal = canonocalize(p2);

        const u32 run = std::abs(static_cast<long>(p1_normal.x - p2_normal.x));
        const u32 rise = std::abs(static_cast<long>(p1_normal.y - p2_normal.y));

        if (run > rise)
        {
            draw_horizontal_line(p1_normal, p2_normal, color);
        }
        else
        {
            draw_vertical_line(p1_normal, p2_normal, color);
        }
    }

    void Renderer::draw_triangle(Vec4 p1, Vec4 p2, Vec4 p3, Color color)
    {
        draw_line(p1, p2, color);
        draw_line(p2, p3, color);
        draw_line(p3, p1, color);
    }

    void Renderer::clear(Color color)
    {
        fill_rect(0, 0, m_logical_width - 1, m_logical_height - 1, color);
    }

    void Renderer::display()
    {
        int texture_pitch = 0;
        void* texture_pixels = nullptr;
        SDL_LockTexture(m_texture, nullptr, &texture_pixels, &texture_pitch);
        std::memcpy(texture_pixels, m_frame_buffer.data(), texture_pitch * m_logical_height);
        SDL_UnlockTexture(m_texture);

        SDL_RenderClear(m_renderer);
        SDL_RenderTexture(m_renderer, m_texture, nullptr, nullptr);
        SDL_RenderPresent(m_renderer);
    }
}
