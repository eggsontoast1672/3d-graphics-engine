#pragma once

namespace rasp
{
    class Engine
    {
    private:
    };
}

typedef void (*UpdateCallback)(void *);

void engine_init(int width, int height, const char *title);
void engine_quit(void);
void engine_set_update_callback(UpdateCallback callback);
void engine_run(void);
