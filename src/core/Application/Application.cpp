#include "Application.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>     //glm::mat4 identity = glm::mat4(1.0f);
#include <glm/gtc/type_ptr.hpp>             //glm::value_ptr

#include "graphics/renderer/Shader.hpp"
#include "graphics/renderer/VertexBuffer.hpp"
#include "graphics/renderer/VertexArray.hpp"
#include "graphics/renderer/ShaderProgram.hpp"
#include "graphics/renderer/ElementBuffer.hpp"

#include "graphics/mesh/Mesh.hpp"

#include "core/Camera.hpp"

#include <array>
#include <memory>       // unique_ptr
#include <fstream>      // read obj file
#include <iostream>
#include <string>
#include <sstream>

namespace core
{
    //Constructor
    Application::Application(): _window(1200, 600, "LearnOpenGL") {}

    int Application::run()
    {
        std::cout << "glfw version: " << glfwGetVersionString() << '\n';
        // glfw: initialize and configure
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if (!_window.create())
        {
            glfwTerminate();
            return -1;
        }

        // Carrega os shaders a partir de um arquivo externo, compila e linka com o programa
        graphics::renderer::ShaderProgram program("shaders/shader.vert","shaders/shader.frag");

        // std::string objFilePath ("resources/teapot.obj");
        graphics::mesh::Mesh mesh("resources/teapot.obj");

        float lastFrameStartTime = 0.0f;
        
        glm::mat4 objPos = glm::mat4(1.0f);
        objPos = glm::translate(objPos, glm::vec3(0.0, -5.0, 0.0));
        objPos = glm::rotate(objPos, glm::radians(-90.0f),glm::vec3(1.0, 0.0, 0.0));
        objPos = glm::scale(objPos, glm::vec3(0.5, 0.5, 0.5));
        program.sendUniform("objPos",objPos);

        auto windowDimensions = _window.getWindowDimensions();
        Camera camera(windowDimensions.first,windowDimensions.second,glm::vec3(0.0f,0.0f,2.0f));

        glEnable(GL_DEPTH_TEST);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // render loop
        while (!_window.shouldClose())
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            program.use();
            camera.Matrix(45.0f,0.1f,100.0f,program,"camMatrix");
            program.sendUniform("objPos",objPos);

            glPointSize(1.0f);
            if (glfwGetKey(_window.getGLFWwindow(), GLFW_KEY_M) == GLFW_PRESS)
            {
                if (first_m_ButtonClick)
                {
                    _activatePointsVisualization = !_activatePointsVisualization;
                    first_m_ButtonClick = false;
                }
            }

            if (glfwGetKey(_window.getGLFWwindow(), GLFW_KEY_M) == GLFW_RELEASE)
            {
                first_m_ButtonClick = true;
            }

            if(_activatePointsVisualization)
                mesh.drawPointCloud();
            else
                mesh.draw();

            [[maybe_unused]] auto deltaTime = calculateDeltaTime(lastFrameStartTime);
            _window.swapBuffers();
            _window.pollEvents();
            _window.processInput();
            camera.Inputs(_window.getGLFWwindow(),deltaTime);
            program.recompileShaders(_window.getGLFWwindow());
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
} // namespace core
