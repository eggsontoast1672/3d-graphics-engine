#pragma once

#include <vector>

#include <SDL3/SDL.h>

#include "raspberry/types.hpp"

namespace rasp
{
    struct Color
    {
        u8 r;
        u8 g;
        u8 b;
    };

    class Renderer
    {
    public:
        Renderer(const char* title, u16 width, u16 height);
        ~Renderer();

        void fill_pixel(u16 x, u16 y, Color color);
        void fill_rect(u16 x0, u16 y0, u16 x1, u16 y1, Color color);

    private:
        void draw_horizontal_line(u16 x0, u16 y0, u16 x1, u16 y1, Color color);
        void draw_vertical_line(u16 x0, u16 y0, u16 x1, u16 y1, Color color);

    public:
        void draw_line(u16 x0, u16 y0, u16 x1, u16 y1, Color color);
        void clear(Color color);
        void display();

    private:
        u16 m_logical_width;
        u16 m_logical_height;
        std::vector<u8> m_frame_buffer;

        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        SDL_Texture* m_texture;
    };
}
