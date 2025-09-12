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
            void loadObjFile(std::vector<float> &vertices, const char * objFilePath);
            float calculateDeltaTime(float &lastFrameStartTime);
        private:
            graphics::Window _window;

            //Default positions to debug
            std::vector<float> _positions={
                0.0f,0.0f,0.0f,
                1.0f,0.0f,0.0f,
                0.0f,1.0f,0.0f,
                1.0f,1.0f,0.0f,
                0.0f,0.0f,1.0f,
                1.0f,0.0f,1.0f,
                0.0f,1.0f,1.0f,
                1.0f,1.0f,1.0f
            };

            std::vector<int> triangleIndex;

            bool _activatePointsVisualization = false;
            bool first_m_ButtonClick = true;
    };

} // namespace core
