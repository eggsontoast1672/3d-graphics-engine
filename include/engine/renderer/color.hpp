#pragma once

#include <cstdint>

namespace rasp
{
    /// An RGB color.
    struct Color
    {
        std::uint8_t r;
        std::uint8_t g;
        std::uint8_t b;
    };

    constexpr Color COLOR_BLACK = {0x00, 0x00, 0x00};
    constexpr Color COLOR_RED = {0xff, 0x00, 0x00};
}
