use macroquad::prelude::*;

/// A triangle in 3D space.
#[derive(Clone, Copy)]
pub struct Triangle3(pub Vec3, pub Vec3, pub Vec3);

impl Triangle3 {
    pub fn homogenize(self) -> Triangle4 {
        let Self(v1, v2, v3) = self;

        Triangle4(
            Vec4::new(v1.x, v1.y, v1.z, 1.0),
            Vec4::new(v2.x, v2.y, v2.z, 1.0),
            Vec4::new(v3.x, v3.y, v3.z, 1.0),
        )
    }
}

#[derive(Clone, Copy)]
pub struct Triangle4(pub Vec4, pub Vec4, pub Vec4);

impl Triangle4 {
    pub fn transform(self, matrix: Mat4) -> Self {
        let Self(v1, v2, v3) = self;

        Self(matrix * v1, matrix * v2, matrix * v3)
    }

    pub fn normalize(self) -> Triangle3 {
        let Self(v1, v2, v3) = self;

        Triangle3(v1.xyz() / v1.w, v2.xyz() / v2.w, v3.xyz() / v3.w)
    }
}

#[derive(Clone, Copy)]
pub struct Face {
    pub vertex_indices: [usize; 3],
    pub normal_index: Option<usize>,
}

/// A 3D mesh.
#[derive(Clone)]
pub struct Mesh {
    pub vertices: Vec<Vec3>,
    pub normals: Vec<Vec3>,
    pub faces: Vec<Face>,
}

fn parse_vector_line<'a, I>(line_parts: &mut I, vectors: &mut Vec<Vec3>)
where
    I: Iterator<Item = &'a str>,
{
    let mut components = [0.0f32; 3];
    for i in 0..3 {
        components[i] = line_parts.next().unwrap().parse().unwrap();
    }

    vectors.push(Vec3::from_array(components));
}

fn parse_face_line<'a, I>(line_parts: &mut I, faces: &mut Vec<Face>)
where
    I: Iterator<Item = &'a str>,
{
    let mut vertex_indices: [usize; _] = [0; 3];
    let mut normal_index = None;

    for i in 0..3 {
        let mut index_parts = line_parts.next().unwrap().split('/');
        vertex_indices[i] = index_parts.next().unwrap().parse().unwrap();
        if i == 2 {
            normal_index = index_parts
                .nth(1)
                .map(|part| part.parse::<usize>().unwrap())
        }
    }

    faces.push(Face {
        vertex_indices,
        normal_index,
    });
}

/// Parsea wavefront object file into a mesh.
///
/// Note that the mesh must be triangulated. All lines of non-vertex data are skipped. Faces are
/// not supported, so vertices must often be duplicated.
pub fn parse_wavefront(source: &str) -> Mesh {
    // 1. Parse the file into a list of vertices and a list of faces
    // 2. Convert the vertex and face data into a list of triangles

    let mut vertices: Vec<Vec3> = Vec::new();
    let mut normals: Vec<Vec3> = Vec::new();
    let mut faces: Vec<Face> = Vec::new();

    for line in source.lines() {
        let mut parts = line.split_whitespace();
        let Some(kind) = parts.next() else {
            // If there is no kind, the line must be blank so we can skip to the next one.
            continue;
        };

        match kind {
            "v" => parse_vector_line(&mut parts, &mut vertices),
            "vn" => parse_vector_line(&mut parts, &mut normals),
            "f" => parse_face_line(&mut parts, &mut faces),
            _ => {}
        }
    }

    Mesh {
        vertices,
        normals,
        faces,
    }
}
