#include "raspberry/renderer.hpp"

#include <cmath>

constexpr int sw = 160;
constexpr int sh = 120;

int main()
{
    rasp::Renderer renderer("3D Renderer", sw, sh);

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        double ticks = SDL_GetTicks() / 1000.0;

        std::size_t start_x = sw / 2.0;
        std::size_t start_y = sh / 2.0;
        std::size_t end_x = sw / 2.0 + sw / 4.0 * std::cos(ticks);
        std::size_t end_y = sh / 2.0 + sh / 4.0 * std::sin(ticks);

        renderer.clear(rasp::Color{0x00, 0x00, 0x00});
        // renderer.fill_rect(100, 100, 200, 200, rasp::Color{0xff, 0x00, 0x00});
        renderer.fill_pixel(end_x, end_y, rasp::Color{0x00, 0x00, 0xff});
        renderer.draw_line(start_x, start_y, end_x, end_y, rasp::Color{0x00, 0xff, 0x00});
        renderer.display();
    }
}
