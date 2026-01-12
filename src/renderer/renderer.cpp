#include "engine/renderer/renderer.h"

#include "engine/image.h"
#include "engine/texture.h"
#include "engine/renderer/color.h"

/**
 * The renderer frame buffer.
 */
static Image s_buffer = {0};

bool renderer_init(int width, int height)
{
    return image_create(width, height, &s_buffer);
}

void renderer_quit(void)
{
    image_delete(&s_buffer);
}

void renderer_clear(Color color)
{
    renderer_fill_rect(0, 0, s_buffer.width, s_buffer.height, color);
}

void renderer_fill_pixel(int x, int y, Color color)
{
    // We do not perform any bounds checking on the index for speed reasons.
    int index = (y * s_buffer.width + x) * 3;

    s_buffer.data[index] = color.r;
    s_buffer.data[index + 1] = color.g;
    s_buffer.data[index + 2] = color.b;
}

void renderer_fill_rect(int x1, int x2, int y1, int y2, Color color)
{
    for (int y = y1; y < y2; y++)
    {
        for (int x = x1; x < x2; x++)
        {
            renderer_fill_pixel(x, y, color);
        }
    }
}

void renderer_display(void)
{
    engine_texture_set_data(&s_buffer);
}
