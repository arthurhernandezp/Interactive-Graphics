#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "graphics/window/WindowFramework.hpp"

namespace core
{
    class Application {
    public:
        Application();

        int run();

    private:
        graphics::Window m_window;
        void changeBackgroundColor();
        void processInput(GLFWwindow* window);
    };

} // namespace core
