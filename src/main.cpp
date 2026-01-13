#include "raspberry/renderer.hpp"

int main()
{
    rasp::Renderer renderer("3D Renderer", 640, 480);

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
        renderer.fill_rect(100, 100, 200, 200, rasp::Color{0xff, 0x00, 0x00});
        renderer.display();
    }
}
