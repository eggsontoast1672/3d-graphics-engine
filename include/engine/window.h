#pragma once

#include <stdbool.h>

bool engine_window_init(int width, int height, const char *title);
void engine_window_quit(void);
bool engine_window_should_close(void);
void engine_window_clear(void);
void engine_window_swap_buffers(void);
void engine_window_poll_events(void);
