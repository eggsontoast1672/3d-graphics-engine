#pragma once

#include <type_traits>

namespace rasp
{
    template <typename Number>
    struct Vec3
    {
        // It would be preferable if we could only use the vector class for
        // types which have sensible notions of addition and multiplication,
        // essentially like a commutative ring.
        static_assert(std::is_arithmetic_v<Number>);

        Number x;
        Number y;
        Number z;

        Vec3 operator+(Vec3 rhs)
        {
            return Vec3{
                .x = this->x + rhs.x,
                .y = this->y + rhs.y,
                .z = this->z + rhs.z,
            };
        }

        Vec3 operator-(Vec3 rhs)
        {
            return Vec3{
                .x = this->x - rhs.x,
                .y = this->y - rhs.y,
                .z = this->z - rhs.z,
            };
        }

        Vec3 operator*(Number rhs)
        {
            return Vec3{
                .x = this->x * rhs,
                .y = this->y * rhs,
                .z = this->z * rhs,
            };
        }

        Vec3 operator/(Number rhs)
        {
            return Vec3{
                .x = this->x / rhs,
                .y = this->y / rhs,
                .z = this->z / rhs,
            };
        }
    };
}
