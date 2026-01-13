#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

namespace rasp
{
    struct Color;

    /// An in-memory buffer of RGB pixel data.
    class Image
    {
    public:
        /// Create a blank image with the specified dimensions.
        Image(int width, int height);

        /// Get the width of the image.
        int get_width() const;

        /// Get the height of the image.
        int get_height() const;

        /// Get the pixel data.
        const std::uint8_t* get_pixels() const;

        /// Set a pixel of the image to the specified color.
        ///
        /// If the location of the pixel is outside of the bounds of the image,
        /// a `std::out_of_range` exception is thrown.
        void set_pixel(std::size_t x, std::size_t y, Color color);

        /// Dump the image data to a PPM file.
        void dump_to_ppm(const std::filesystem::path& path) const;

    private:
        int m_width;
        int m_height;
        std::vector<std::uint8_t> m_pixels;
    };
}
