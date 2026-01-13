#include "raspberry/renderer.hpp"

#include <cstdlib>
#include <utility>

namespace rasp
{
    Renderer::Renderer(const char* title, std::uint16_t width, std::uint16_t height)
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

    void Renderer::fill_pixel(std::size_t x, std::size_t y, Color color)
    {
        const std::size_t index = (y * m_logical_width + x) * 3;

        m_frame_buffer.at(index) = color.r;
        m_frame_buffer.at(index + 1) = color.g;
        m_frame_buffer.at(index + 2) = color.b;
    }

    void Renderer::fill_rect(std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, Color color)
    {
        for (std::size_t y = y1; y < y2; y++)
        {
            for (std::size_t x = x1; x < x2; x++)
            {
                fill_pixel(x, y, color);
            }
        }
    }

    void Renderer::draw_horizontal_line(int x0, int y0, int x1, int y1, Color color)
    {
        if (x0 > x1)
        {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }

        const int dx = x1 - x0;
        int dy = y1 - y0;
        const int dir = dy < 0 ? -1 : 1;
        dy *= dir;

        int y = y0;
        int d = 2 * dy - dx;

        for (int x = x0; x <= x1; x++)
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

    void Renderer::draw_vertical_line(int x0, int y0, int x1, int y1, Color color)
    {
        if (y0 > y1)
        {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }

        int dx = x1 - x0;
        const int dy = y1 - y0;
        const int dir = dx < 0 ? -1 : 1;
        dx *= dir;

        int x = x0;
        int d = 2 * dx - dy;

        for (int y = y0; y <= y1; y++)
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

    void Renderer::draw_line(int x0, int y0, int x1, int y1, Color color)
    {
        if (std::abs(x0 - x1) > std::abs(y0 - y1))
        {
            draw_horizontal_line(x0, y0, x1, y1, color);
        }
        else
        {
            draw_vertical_line(x0, y0, x1, y1, color);
        }
    }

    void Renderer::clear(Color color)
    {
        fill_rect(0, 0, m_logical_width, m_logical_height, color);
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
