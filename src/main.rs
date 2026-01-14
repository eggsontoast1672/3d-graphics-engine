use sdl3::event::Event;
use sdl3::pixels::PixelFormat;
use sdl3::render::ScaleMode;

const LW: u32 = 40;
const LH: u32 = 30;

fn make_screen() -> Box<[u8]> {
    vec![0; (LW * LH * 3) as usize].into_boxed_slice()
}

fn main() {
    let mut screen = make_screen();

    let sdl_context = sdl3::init().unwrap();
    let video_subsystem = sdl_context.video().unwrap();
    let _window = video_subsystem
        .window("Raspberry Engine", 800, 600)
        .build()
        .unwrap();

    let mut canvas = _window.into_canvas();
    let texture_creator = canvas.texture_creator();
    let mut texture = texture_creator
        .create_texture_streaming(PixelFormat::RGB24, 40, 30)
        .unwrap();

    texture.set_scale_mode(ScaleMode::Nearest);

    let mut event_pump = sdl_context.event_pump().unwrap();

    'running: loop {
        for event in event_pump.poll_iter() {
            match event {
                Event::Quit { .. } => break 'running,
                _ => {}
            }
        }

        let ticks = sdl3::timer::ticks() as f64 / 100.0;

        for y in 0..LH {
            for x in 0..LW {
                let index = (y * LW + x) as usize * 3;
                let angle = x as f64 + y as f64 + ticks;
                let red = angle.cos().abs();
                let blue = angle.sin().abs();

                screen[index] = (red * 255.0) as u8;
                screen[index + 1] = 127;
                screen[index + 2] = (blue * 255.0) as u8;
            }
        }

        texture.update(None, &screen, LW as usize * 3).unwrap();

        canvas.clear();
        canvas.copy(&texture, None, None).unwrap();
        canvas.present();
    }
}
