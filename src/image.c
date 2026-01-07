#include "engine/image.h"

#include <stdint.h>
#include <stdlib.h>

bool image_create(int width, int height, Image *image)
{
    if (image->data != NULL)
    {
        return true;
    }

    uint8_t *const data = calloc(width * height * 3, 1);
    if (data == NULL)
    {
        return false;
    }

    image->width = width;
    image->height = height;
    image->data = data;

    return true;
}

void image_set_pixel(const Image *image, size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b)
{
    size_t index = (y * image->width + x) * 3;

    image->data[index] = r;
    image->data[index + 1] = g;
    image->data[index + 2] = b;
}

void image_delete(Image *image)
{
    free(image->data);

    image->width = 0;
    image->height = 0;
    image->data = NULL;
}
