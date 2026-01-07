#include "engine/image.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

bool image_create(int width, int height, Image *image)
{
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

bool image_dump_to_ppm(const Image *image, const char *path)
{
    FILE *file = fopen(path, "w");
    if (file == NULL)
    {
        return false;
    }

    fprintf(file, "P3\n%d %d\n255\n", image->width, image->height);

    for (size_t i = 0; i < image->width * image->height * 3; i += 3)
    {
        uint8_t r = image->data[i];
        uint8_t g = image->data[i + 1];
        uint8_t b = image->data[i + 2];

        fprintf(file, "%uhh %uhh %uhh\n", r, g, b);
    }

    fclose(file);

    return true;
}

void image_delete(Image *image)
{
    free(image->data);

    image->width = 0;
    image->height = 0;
    image->data = NULL;
}
