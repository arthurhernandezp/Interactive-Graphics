#include "Application.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>     //glm::mat4 identity = glm::mat4(1.0f);
#include <glm/gtc/type_ptr.hpp>             //glm::value_ptr
#include "graphics/renderer/Shader.hpp"
#include "graphics/renderer/VertexBuffer.hpp"
#include "graphics/renderer/VertexArray.hpp"
#include "graphics/renderer/ShaderProgram.hpp"
#include "graphics/renderer/ElementBuffer.hpp"
#include <array>
#include <memory>       // unique_ptr
#include <fstream>      // read obj file
#include <iostream>
#include <string>
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

        graphics::renderer::ShaderProgram program("shaders/shader.vert","shaders/shader.frag");

        loadObjFile(_positions,"resources/teapot.obj");

        //Criar o VAO
        graphics::renderer::VertexArrayObject vao;
        vao.bindBuffer();

        //Colocar os dados no buffer(VBO)
        graphics::renderer::VertexBufferObject vbo;

        vbo.receiveData(_positions,GL_STATIC_DRAW);

        GLuint pos = program.getAttribLocation("pos");
        vao.LinkVBO(vbo,pos);

        // Unbind all to prevent accidentally modifying them
        vao.unbindBuffer();
        vbo.unbindBuffer();

        // Defina a matriz identidade (4x4)
        glm::mat4 mvp = glm::mat4(1.0f);
        mvp *= glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        float intensity = 1.0f;
        float transparency = 0.5f;

        program.sendUniformMat4("mvp",mvp);
        program.sendUniformFloat("intensity",intensity);
        program.sendUniformFloat("transparency",transparency);

        [[maybe_unused]]auto num_points = _positions.size();
        float lastFrameStartTime = 0.0f;
        float red= 0.0f;
        int factor = 1;

        // render loop
        while (!_window.shouldClose())
        {
            program.use();
            vao.bindBuffer();

            float currentFrameStartTime = static_cast<float>(glfwGetTime());
            float deltaTime = currentFrameStartTime - lastFrameStartTime;
            lastFrameStartTime = currentFrameStartTime;

            _window.processInput();
            _window.animateBackgroundColor(red, factor, deltaTime);
            intensity -= (0.08f * deltaTime) * factor;

            program.sendUniformFloat("intensity",intensity);
            program.sendUniformFloat("transparency",intensity);
            // mvp = glm::translate(glm::mat4(1.0f), glm::vec3(red, 0.0f, 0.0f ));
            mvp *= glm::rotate(glm::mat4(1.0f), glm::radians(deltaTime*20), glm::vec3(1.0f, 0.0f, 0.0f));
            program.sendUniformMat4("mvp", mvp);

            // render
            glClearColor(red, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glPointSize(1.5f);
            glDrawArrays(GL_POINTS,
            0,num_points);

            _window.swapBuffers();
            _window.pollEvents();
        }

        glfwTerminate();
        return 0;
    }

    void Application::loadObjFile(std::vector<float> &vertices,const char *objFilePath) const
    {
        //Loads OBJ file from path
        std::ifstream file;
        file.open(objFilePath);
        if (!file.good())
        {
            std::cout << "Can't open obj file " << objFilePath << std::endl;
            return;
        }
        
        vertices.clear();

        std::string line;
        while (std::getline(file, line))
        {
            std::string text;

            file >> text;
            if (text == "v")
            {
                float value;
                file >> value;
                vertices.emplace_back(value);

                file >> value;
                vertices.emplace_back(value);

                file >> value;
                vertices.emplace_back(value);

            }
        }
    }
} // namespace core
