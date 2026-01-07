#pragma once

#include <GL/glew.h>

#include "engine/image.h"

GLuint texture_create(void);
void texture_set_data(const Image *image);
