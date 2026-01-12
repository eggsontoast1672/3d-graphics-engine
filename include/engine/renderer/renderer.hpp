#pragma once

#include <stdbool.h>

#include "engine/renderer/color.h"

/**
 * Initialize the renderer.
 *
 * @param width The logical width of the renderer buffer.
 * @param height The logical height of the renderer buffer.
 * @return true if initialization succeeded, false otherwise.
 */
bool renderer_init(int width, int height);

/**
 * Free the renderer's resources.
 */
void renderer_quit(void);

/**
 * Clear the screen.
 *
 * @param color The color to use for clearing.
 */
void renderer_clear(Color color);

/**
 * Fill a pixel on the screen.
 *
 * @param x The x position of the pixel.
 * @param y The y position of the pixel.
 * @param color The color of the pixel.
 */
void renderer_fill_pixel(int x, int y, Color color);

/**
 * Fill a rectangle on the screen.
 *
 * @param x1 The x coordinate of the top left corner.
 * @param y1 The y coordinate of the top left corner.
 * @param x2 The x coordinate of the bottom right corner.
 * @param y2 The y coordinate of the bottom right corner.
 * @param color The color of the rectangle.
 */
void renderer_fill_rect(int x1, int x2, int y1, int y2, Color color);

/**
 * Display the pixel buffer to the screen.
 */
void renderer_display(void);
