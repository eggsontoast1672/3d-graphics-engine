#include "engine/image.hpp"

#include <fstream>

namespace rasp
{
    Image::Image(int width, int height)
        : m_width(width),
          m_height(height),
          m_pixels(static_cast<decltype(m_pixels)::size_type>(width * height * 3))
    {
    }

    void Image::set_pixel(std::size_t x, std::size_t y, Color color)
    {
        const std::size_t index = (y * m_width + x) * 3;

        m_pixels.at(index) = color.r;
        m_pixels.at(index + 1) = color.g;
        m_pixels.at(index + 2) = color.b;
    }

    void Image::dump_to_ppm(const std::filesystem::path &path) const
    {
        std::ofstream file(path);

        file << "P3\n" << m_width << ' ' << m_height << "\n255\n";

        for (std::size_t i = 0; i < m_width * m_height * 3; i += 3)
        {
            std::uint8_t r = m_pixels[i];
            std::uint8_t g = m_pixels[i + 1];
            std::uint8_t b = m_pixels[i + 2];

            file << r << ' ' << g << ' ' << b << '\n';
        }
    }
}
