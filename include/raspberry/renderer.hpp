#pragma once

#include <vector>

#include <SDL3/SDL.h>

#include "raspberry/model.hpp"
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

        /// Canonicalize the given vector.
        ///
        /// The input vector is first normalized by the homogeneous coordinate,
        /// and then the viewport transform is applied to the vector to figure
        /// out where it lands in integer coordinates.
        [[nodiscard]] UVec2 canonocalize(Vec4 vertex) const;

        void fill_pixel(u16 x, u16 y, Color color);
        void fill_rect(u16 x0, u16 y0, u16 x1, u16 y1, Color color);

    private:
        /// Draw a line segment between the specified endpoints in the specified
        /// color, whose slope is within the range (-1, 1).
        void draw_horizontal_line(UVec2 p1, UVec2 p2, Color color);

        /// Draw a line segment between the specified endpoints in the specified
        /// color, whose slope is within the range (inf, -1] U [1, inf).
        void draw_vertical_line(UVec2 p1, UVec2 p2, Color color);

    public:
        /// Draw a line segment between the specified endpoints in the specified
        /// color.
        void draw_line(Vec4 p1, Vec4 p2, Color color);

        /// Draw the boundary of the triangle whose vertices sit at the three
        /// points provided, in the specified color.
        void draw_triangle(Vec4 p1, Vec4 p2, Vec4 p3, Color color);

        /// Draw the wireframe for a model in the specified color.
        void draw_model(const Model& model, Color color);

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
