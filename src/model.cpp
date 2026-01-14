#include "raspberry/model.hpp"

#include <utility>
#include <vector>

#include "raspberry/math.hpp"
#include "raspberry/types.hpp"

namespace rasp
{
    Model::Model(std::vector<Vec3<f32>>&& vertices, std::vector<Face>&& faces)
        : m_vertices(std::move(vertices)), m_faces(std::move(faces))
    {
    }

    Model Model::square(f32 side_length)
    {
        const f32 half_length = side_length * 0.5f;

        std::vector<Vec3<f32>> vertices{
            Vec3<f32>{-half_length, half_length, 0.0f},
            Vec3<f32>{half_length, half_length, 0.0f},
            Vec3<f32>{-half_length, -half_length, 0.0f},
            Vec3<f32>{half_length, -half_length, 0.0f},
        };

        std::vector<Face> faces{
            Face{{0, 1, 2}},
            Face{{1, 2, 3}},
        };

        return Model(std::move(vertices), std::move(faces));
    }
}
