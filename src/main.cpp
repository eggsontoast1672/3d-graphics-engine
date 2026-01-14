#include <cmath>

#include "raspberry/model.hpp"
#include "raspberry/renderer.hpp"

constexpr int sw = 160;
constexpr int sh = 120;

int main()
{
    rasp::Renderer renderer("3D Renderer", sw, sh);
    auto square = rasp::Model::square(2.0f);
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

        renderer.clear(rasp::Color{0x00, 0x00, 0x00});
        renderer.draw_model(square, rasp::Color{0xff, 0x00, 0x00});
        renderer.display();
    }
}
