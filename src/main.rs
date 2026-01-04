use macroquad::prelude::*;

use engine::mesh::{self, Mesh};

fn transform_viewport(vertex: Vec2) -> Vec2 {
    // Assume that coordinates work as in OpenGL.

    let x = (vertex.x + 1.0) * screen_width() / 2.0;
    let y = (vertex.y + 1.0) * screen_height() / 2.0;

    Vec2::new(x, y)
}

fn render_mesh(mesh: &Mesh, transform: Mat4) {
    const LIGHT_DIRECTION: Vec3 = Vec3::NEG_Z;

    let proj = Mat4::perspective_rh_gl(
        std::f32::consts::FRAC_PI_3,
        screen_width() / screen_height(),
        0.1,
        100.0,
    );

    let norm_mat = transform.inverse().transpose();

    for face in &mesh.faces {
        let v1 = mesh.vertices[face.vertex_indices[0] - 1];
        let v2 = mesh.vertices[face.vertex_indices[1] - 1];
        let v3 = mesh.vertices[face.vertex_indices[2] - 1];
        let normal = face.normal_index.map(|i| mesh.normals[i - 1]).unwrap_or(Vec3::Y);

        let v1_transformed = transform * v1.extend(1.0);
        let v2_transformed = transform * v2.extend(1.0);
        let v3_transformed = transform * v3.extend(1.0);
        let normal_transformed = Vec4::xyz(norm_mat * normal.extend(1.0)).normalize();

        // Check if we can cull the face.
        if normal_transformed.dot(v1_transformed.xyz() / v1_transformed.w) >= 0.0 {
            continue;
        }

        let v1_projected = proj * v1_transformed;
        let v2_projected = proj * v2_transformed;
        let v3_projected = proj * v3_transformed;

        // Compute light intensity.
        let light_intensity = -normal_transformed.dot(LIGHT_DIRECTION);

        draw_triangle(
            transform_viewport(v1_projected.xy() / v1_projected.w),
            transform_viewport(v2_projected.xy() / v2_projected.w),
            transform_viewport(v3_projected.xy() / v3_projected.w),
            Color::from_vec(Vec3::extend(Vec3::ONE * light_intensity, 1.0))
        );
    }
}

#[macroquad::main("3D Graphics Engine")]
async fn main() {
    let source = std::fs::read_to_string("ship.obj").unwrap();
    let cube_mesh = mesh::parse_wavefront(&source);
    let cube_translation = Mat4::from_translation(Vec3::new(0.0, 0.0, -10.0));

    loop {
        let theta = get_time();
        let cube_rotation = Mat4::from_euler(EulerRot::XYZ, theta as f32 / 2.0, theta as f32, 0.0);
        let cube_transform = cube_translation * cube_rotation;

        clear_background(BLACK);
        render_mesh(&cube_mesh, cube_transform);
        next_frame().await;
    }
}
