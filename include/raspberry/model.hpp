#pragma once

#include <array>
#include <vector>

#include "raspberry/math.hpp"
#include "raspberry/types.hpp"

namespace rasp
{
    /// A face of a model.
    ///
    /// Each face is defined by the indices of the vectors that make up the
    /// triangle, as well as possibly some texture and normal information.
    struct Face
    {
        std::array<usize, 3> vertex_indices;
    };

    /// A 3D model.
    class Model
    {
    public:
        /// Create a new model from vertex and face data.
        Model(std::vector<Vec3<f32>>&& vertices, std::vector<Face>&& faces);

        /// Create a square model.
        ///
        /// The square sits inside the xy-plane and its center is at the origin.
        /// Its side length is as specified.
        static Model square(f32 side_length);

    private:
        std::vector<Vec3<f32>> m_vertices;
        std::vector<Face> m_faces;
    };
}
