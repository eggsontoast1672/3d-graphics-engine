#include "raspberry/renderer.hpp"

#include <cstdlib>

namespace rasp
{
    Renderer::Renderer(const char* title, std::uint16_t width, std::uint16_t height)
        : m_logical_width(width),
          m_logical_height(height),
          m_frame_buffer(static_cast<decltype(m_frame_buffer)::size_type>(width * height * 3))
    {
        SDL_Init(SDL_INIT_VIDEO);

        m_window = SDL_CreateWindow(title, width, height, 0);
        m_renderer = SDL_CreateRenderer(m_window, nullptr);
        m_texture = SDL_CreateTexture(
            m_renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING,
            width, height);
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

    void Renderer::draw_line(int x0, int y0, int x1, int y1, Color color)
    {
        const int dx = x1 - x0;
        const int dy = y1 - y0;

        if (dy < dx) // The line is not steep (slope between -1 and 1)
        {
            int d = 2 * dy - dx;
            int y = y0;

            for (int x = x0; x <= x1; x++)
            {
                fill_pixel(x, y, color);

                if (d > 0)
                {
                    y = y + 1;
                    d = d + (2 * (dy - dx));
                }
                else
                {
                    d = d + 2 * dy;
                }
            }
        }

        // Line is steep (slope greater than 1 or less than -1)
        else
        {
            int d = 2 * dx - dy;
            int x = x0;

            for (int y = y0; y <= y1; y++)
            {
                fill_pixel(x, y, color);

                if (d > 0)
                {
                    x = x + 1;
                    d = d + (2 * (dx - dy));
                }
                else
                {
                    d = d + 2 * dx;
                }
            }
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
