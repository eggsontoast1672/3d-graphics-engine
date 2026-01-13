#include <cstdint>
#include <cstring>
#include <vector>

#include <SDL3/SDL.h>

struct Color
{
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
};

class Renderer
{
public:
    Renderer(const char* title, std::uint16_t width, std::uint16_t height)
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

    ~Renderer()
    {
        SDL_DestroyTexture(m_texture);
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
    }

    void fill_pixel(std::size_t x, std::size_t y, Color color)
    {
        const std::size_t index = (y * m_logical_width + x) * 3;

        m_frame_buffer.at(index) = color.r;
        m_frame_buffer.at(index + 1) = color.g;
        m_frame_buffer.at(index + 2) = color.b;
    }

    void fill_rect(std::size_t x1, std::size_t y1, std::size_t x2, std::size_t y2, Color color)
    {
        for (std::size_t y = y1; y < y2; y++)
        {
            for (std::size_t x = x1; x < x2; x++)
            {
                fill_pixel(x, y, color);
            }
        }
    }

    void clear(Color color)
    {
        fill_rect(0, 0, m_logical_width, m_logical_height, color);
    }

    void display()
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

private:
    std::size_t m_logical_width;
    std::size_t m_logical_height;
    std::vector<std::uint8_t> m_frame_buffer;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
};

int main()
{
    Renderer renderer("3D Renderer", 640, 480);

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

        renderer.clear(Color{0x00, 0x00, 0x00});
        renderer.fill_rect(100, 100, 200, 200, Color{0xff, 0x00, 0x00});
        renderer.display();
    }
}
