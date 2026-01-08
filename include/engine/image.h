#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define IMAGE_BYTE_COUNT(image) ((image).width * (image).height * 3)

typedef struct {
    int width;
    int height;
    uint8_t *data;
} Image;

bool image_create(int width, int height, Image *image);
bool image_set_pixel(const Image *image, size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b);
bool image_dump_to_ppm(const Image *image, const char *path);
void image_delete(Image *image);
