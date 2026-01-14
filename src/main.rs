use raspberry::renderer::Renderer;

fn main() {
    const WIDTH: u32 = 40;
    const HEIGHT: u32 = 30;
    const SCALE: u32 = 20;

    let mut renderer = Renderer::new(WIDTH, HEIGHT, SCALE);

    while renderer.is_running() {
        renderer.clear();

        let ticks = sdl3::timer::ticks() as f32 / 1000.0;

        for y in 0..HEIGHT {
            for x in 0..WIDTH {
                let angle = x as f32 / 40.0 + y as f32 / 30.0 + ticks;
                let color = sdl3::pixels::FColor {
                    r: (angle * 2.0).cos().abs(),
                    g: (angle * 3.0).cos().abs(),
                    b: angle.sin().abs(),
                    a: 1.0,
                };

                renderer.draw_pixel(x, y, color);
            }
        }

        renderer.display();
    }
}
