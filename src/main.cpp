#include <cstdint>
#include <cstring>

#include <SDL3/SDL.h>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

static constexpr std::size_t screen_width = 160;
static constexpr std::size_t screen_height = 90;
static std::uint32_t screen[screen_width * screen_height];
static SDL_Texture* texture = nullptr;

int main()
{
    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, screen_width, screen_height);
    if (!texture)
    {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    for (std::size_t i = 0; i < screen_width * screen_height; i++)
    {
        screen[i] = 0xFF0000FF;
    }

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

        int texture_pitch = 0;
        void* texture_pixels = nullptr;
        if (!SDL_LockTexture(texture, nullptr, &texture_pixels, &texture_pitch))
        {
            SDL_Log("Failed to lock texture: %s\n", SDL_GetError());
            return SDL_APP_FAILURE;
        }

        std::memcpy(texture_pixels, screen, texture_pitch * screen_height);
        SDL_UnlockTexture(texture);

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }
}
