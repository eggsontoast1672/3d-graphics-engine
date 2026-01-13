#pragma once

namespace rasp
{
    class Engine
    {
    public:
        virtual bool on_user_create() = 0;
        virtual bool on_user_update(float elapsed_time) = 0;

        void start()
        {
            if (!on_user_create())
            {
                return;
            }
        }
    };
}
