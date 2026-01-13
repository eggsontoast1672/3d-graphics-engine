#pragma once

#include <cstdint>
#include <cstring>
#include <vector>

#include <SDL3/SDL.h>

namespace rasp
{
    struct Color
    {
        std::uint8_t r;
        std::uint8_t g;
        std::uint8_t b;
    };

    class Renderer
    {
    public:
        Renderer(const char* title, std::uint16_t width, std::uint16_t height);
        ~Renderer();

        void fill_pixel(std::size_t x, std::size_t y, Color color);
        void fill_rect(std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, Color color);
        void draw_line(int x1, int y1, int x2, int y2, Color color);
        void clear(Color color);
        void display();

    private:
        std::size_t m_logical_width;
        std::size_t m_logical_height;
        std::vector<std::uint8_t> m_frame_buffer;

        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        SDL_Texture* m_texture;
    };
}
