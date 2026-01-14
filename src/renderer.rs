use sdl3::event::Event;
use sdl3::pixels::{FColor, PixelFormat};
use sdl3::render::{ScaleMode, TextureCreator, WindowCanvas};
use sdl3::video::WindowContext;
use sdl3::{EventPump, Sdl, VideoSubsystem};

pub struct Renderer {
    _sdl: Sdl,
    _video: VideoSubsystem,
    canvas: WindowCanvas,
    texture_creator: TextureCreator<WindowContext>,
    // texture: Texture<'a>,
    event_pump: EventPump,
    width: u32,
    height: u32,
    framebuffer: Box<[u8]>,
}

impl Renderer {
    pub fn new(width: u32, height: u32, scale: u32) -> Self {
        let sdl = sdl3::init().unwrap();
        let video = sdl.video().unwrap();
        let canvas = video
            .window("Raspberry Engine", width * scale, height * scale)
            .build()
            .unwrap()
            .into_canvas();

        let texture_creator = canvas.texture_creator();
        let event_pump = sdl.event_pump().unwrap();
        let framebuffer_size = width as usize * height as usize * 3;
        let framebuffer = vec![0; framebuffer_size].into_boxed_slice();

        Self {
            _sdl: sdl,
            _video: video,
            canvas,
            texture_creator,
            event_pump,
            width,
            height,
            framebuffer,
        }
    }

    pub fn is_running(&mut self) -> bool {
        self.event_pump
            .poll_iter()
            .find(|event| matches!(event, Event::Quit { .. }))
            .is_none()
    }

    pub fn clear(&mut self) {
        for y in 0..self.height {
            for x in 0..self.width {
                self.draw_pixel(x, y, FColor::BLACK);
            }
        }
    }

    pub fn display(&mut self) {
        let mut texture = self
            .texture_creator
            .create_texture_static(PixelFormat::RGB24, self.width, self.height)
            .unwrap();

        texture.set_scale_mode(ScaleMode::Nearest);
        texture.update(None, &self.framebuffer, self.width as usize * 3).unwrap();

        self.canvas.clear();
        self.canvas.copy(&texture, None, None).unwrap();
        self.canvas.present();
    }

    pub fn draw_pixel(&mut self, x: u32, y: u32, color: FColor) {
        let index = (y * self.width + x) as usize * 3;

        self.framebuffer[index] = (color.r * 255.0) as u8;
        self.framebuffer[index + 1] = (color.g * 255.0) as u8;
        self.framebuffer[index + 2] = (color.b * 255.0) as u8;
    }
}
