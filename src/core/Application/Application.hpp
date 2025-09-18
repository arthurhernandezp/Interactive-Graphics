#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <optional>
#include "graphics/window/WindowFramework.hpp"

namespace core
{
    class Application
    {
        public:
            Application();
            int run();
        private:
            float calculateDeltaTime(float &lastFrameStartTime);
        private:
            graphics::Window _window;

            bool _activatePointsVisualization = false;
            bool first_m_ButtonClick = true;
    };

} // namespace core
