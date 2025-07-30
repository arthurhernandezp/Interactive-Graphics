#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "graphics/window/WindowFramework.hpp"

namespace core
{
    class Application 
    {
        public:
            Application();

            int run();

        private:
            void animateBackgroundColor(float &red, int &factor);
            void processInput(GLFWwindow* window);

        private:
            graphics::Window _window;
    };

} // namespace core
