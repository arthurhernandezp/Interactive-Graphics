#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "graphics/renderer/OpenGLContext.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace core      { class Camera; }

namespace graphics
{
    namespace scene         { class Scene;  }

    namespace renderer
    {
        class ShaderProgram;
        
        class Renderer
        {
            public:
                Renderer() = default;
                Renderer(glm::vec3 backgroundColor) : _backgrounColor{backgroundColor} {};
                ~Renderer();
                void init();
                void update(scene::Scene &scene, std::shared_ptr<core::Camera> camera);
                void clear();

                const std::vector<std::shared_ptr<ShaderProgram>>& getShaders() const;
            private:
                void createShadersProgram();
            private:
                // Render state machine
                bool isRunning = false;
                glm::vec3 _backgrounColor = {0.0f,0.0f,0.0f};
                // OPENGL CONTEXT
                std::unique_ptr<graphics::renderer::OpenGLContext> _OpenGLContext;

                // SHADERS PROGRAMS
                std::shared_ptr<ShaderProgram> _meshProgram;
                std::shared_ptr<ShaderProgram> _lightProgram;
                std::vector<std::shared_ptr<ShaderProgram>> _shaders;

        };
    } // namespace renderer
    
} // namespace graphics
