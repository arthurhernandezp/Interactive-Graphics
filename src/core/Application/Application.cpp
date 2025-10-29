#include "Application.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>     //glm::mat4 identity = glm::mat4(1.0f);
#include <glm/gtc/type_ptr.hpp>             //glm::value_ptr

#include "graphics/renderer/OpenGLContext.hpp"

#include "graphics/renderer/ShaderProgram.hpp"

#include "graphics/mesh/Mesh.hpp"
#include "graphics/lighting/Light.hpp"

#include "graphics/scene/SceneObject.hpp"

#include <memory>       // unique_ptr
#include <iostream>

namespace core
{
    //Constructor
    Application::Application(): _window(1200, 600, "LearnOpenGL") {}

    int Application::run()
    {
        std::cout << "glfw version: " << glfwGetVersionString() << '\n';

        graphics::renderer::OpenGLContext OpenGLContext(3,3,GLFW_OPENGL_CORE_PROFILE);

        if (!_window.create())
        {
            glfwTerminate();
            return -1;
        }

        _render.init();

        _scene.load();

        float lastFrameStartTime = 0.0f;

        auto windowDimensions = _window.getWindowDimensions();
        _camera = std::make_shared<Camera>(windowDimensions.first,windowDimensions.second,glm::vec3(0.0f,0.0f,2.0f));

        glEnable(GL_DEPTH_TEST);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // render loop
        while (!_window.shouldClose())
        {
            [[maybe_unused]] auto deltaTime = calculateDeltaTime(lastFrameStartTime);
            _render.clear();
            _scene.update(deltaTime);

            if (glfwGetKey(_window.getGLFWwindow(), GLFW_KEY_M) == GLFW_PRESS)
            {
                if (first_m_ButtonClick)
                {
                    _scene.swapVisualizationMode();
                    first_m_ButtonClick = false;
                }
            }
            if (glfwGetKey(_window.getGLFWwindow(), GLFW_KEY_M) == GLFW_RELEASE)
            {
                first_m_ButtonClick = true;
            }

            _render.update(_scene,_camera);

            _window.swapBuffers();
            _window.pollEvents();
            _window.processInput();
            _camera->Inputs(_window.getGLFWwindow(),deltaTime);

            recompileShaders();
        }

        glfwTerminate();
        return 0;
    }

    float Application::calculateDeltaTime(float &lastFrameStartTime)
    {
        float currentFrameStartTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrameStartTime - lastFrameStartTime;
        lastFrameStartTime = currentFrameStartTime;
        return deltaTime;
    }

    void Application::recompileShaders() const
    {
        auto shaders = _render.getShaders();
        for(auto & shader : shaders)
        {
            shader->recompileShaders(_window.getGLFWwindow());
        }
    }
} // namespace core
