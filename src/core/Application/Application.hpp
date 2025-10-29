#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <optional>
#include "graphics/window/WindowFramework.hpp"
#include "graphics/renderer/Renderer.hpp"
#include "graphics/scene/Scene.hpp"
#include "core/Camera.hpp"

namespace core
{
    class Application
    {
        public:
            Application();
            int run();
        private:
            float calculateDeltaTime(float &lastFrameStartTime);
            void recompileShaders() const;
        private:
            graphics::Window _window;
            graphics::renderer::Renderer _render;
            graphics::scene::Scene _scene;
            std::shared_ptr<Camera> _camera;
            
            bool _activatePointsVisualization = false;
            bool first_m_ButtonClick = true;
    };

} // namespace core
