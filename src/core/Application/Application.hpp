#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "graphics/window/WindowFramework.hpp"

namespace core
{
    class Application
    {
        public:
            Application();

            int run();
        private:
            void animateBackgroundColor(float &red, int &factor, float deltaTime);
            void processInput(GLFWwindow* window);
            std::optional<std::vector<float>> loadObjFile(const char * objFilePath) const;
        private:
            graphics::Window _window;

            std::vector<float> _positions={
                0.8f,0.4f,1.0f,
                0.8f,-0.4f,-0.30f,
                -0.8f,0.4f,0.6f,
                -0.8f,-0.4f,0.0f,
                -0.3f,-0.2f,0.0f,
                0.0f,-0.8f,0.0f
            };
    };

} // namespace core
