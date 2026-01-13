#pragma once

#include <memory>

#include <GLFW/glfw3.h>

namespace rasp
{
    /// A platform agnostic window.
    class Window
    {
    public:
        /// Construct a window.
        Window(int width, int height, const char* title);

        /// Return true if a close event has been detected, false otherwise.
        bool should_close() const;

        /// Clears the window with black.
        void clear() const;

        /// Render the contents of the backbuffer to the screen.
        void display() const;

    private:
        class Deleter
        {
        public:
            void operator()(GLFWwindow* window);
        };

        std::unique_ptr<GLFWwindow, Deleter> m_window;
    };
}
