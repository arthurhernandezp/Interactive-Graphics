#include "Application.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>     //glm::mat4 identity = glm::mat4(1.0f);
#include <glm/gtc/type_ptr.hpp>             //glm::value_ptr
#include "graphics/renderer/Shader.hpp"
#include "graphics/renderer/VertexBuffer.hpp"
#include "graphics/renderer/VertexArray.hpp"
#include "graphics/renderer/ShaderProgram.hpp"
#include <array>
#include <memory>       // unique_ptr
#include <fstream>      // read obj file
#include <iostream>
#include <string>
namespace core
{
    //Constructor
    Application::Application(): _window(800, 600, "LearnOpenGL") {}

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

        // auto loadFileResults = loadObjFile("resources/teapot.obj");
        // if(!loadFileResults)
        // {
        //     std::cout << "FAILED to load file" << '\n';
        // }
        // else{
        //     std::cout << "_positions.size()" << _positions.size() << '\n';
        //     // _positions = loadFileResults.value();
        //     std::cout << "_positions.size()" << _positions.size() << '\n';

        // }
        // [[maybe_unused]] std::array<float,9723> testando;
        // for(int i = 0; auto & v : _positions)
        // {
        //     testando.at(i++) = v;
        // }
        graphics::renderer::ShaderProgram program("shaders/shader.vert","shaders/shader.frag");

        program.use();


        //Criar o VAO
        graphics::renderer::VertexArrayObject vao;
        vao.bindBuffer();
        std::cout << "Criando VAO" << '\n';

        //Colocar os dados no buffer(VBO)
        graphics::renderer::VertexBufferObject vbo;
        vbo.bindBuffer();
        //Receber dados de positions
        vbo.receiveData(_positions,GL_STATIC_DRAW);
        GLuint pos = program.getAttribLocation("pos");
        //Como o opengl irá interpretar esses dados
        vao.LinkVBO(vbo,pos);

        std::vector<float> colors =
        {
            1.0f,0.0f,0.0f,
            0.0f,1.0f,0.0f,
            0.0f,0.0f,1.0f,
            0.0f,1.0f,1.0f,
            1.0f,0.0f,1.0f,
            1.0f,1.0f,0.0f
        };

        graphics::renderer::VertexBufferObject vbo2;
        vbo2.bindBuffer();
        vbo2.receiveData(colors,GL_STATIC_READ);

        GLuint clrLocation = program.getAttribLocation("clr");
        vao.LinkVBO(vbo2,clrLocation);

        // Defina a matriz identidade (4x4)
        glm::mat4 mvp = glm::mat4(1.0f);
        // Envie a matriz MVP para o shader

        std::cout << "Enviando a matriz MVP para o shader" << std::endl;
        program.sendUniformMat4("mvp",mvp);
        program.sendUniformFloat("intensity",0.5f);
        program.sendUniformFloat("transparency",0.2f);

        auto num_points = _positions.size();
        float lastFrameStartTime = 0.0f;
        float red= 0.0f;
        float intensity = 1.0f;
        int factor = 1;
        // render loop

        while (!_window.shouldClose())
        {
            program.use();
            vao.bindBuffer();

            float currentFrameStartTime = static_cast<float>(glfwGetTime());
            float deltaTime = currentFrameStartTime - lastFrameStartTime;
            lastFrameStartTime = currentFrameStartTime;

            processInput(_window.getGLFWwindow());

            animateBackgroundColor(red, factor, deltaTime);
            intensity -= (0.08f * deltaTime) * factor;
            program.sendUniformFloat("intensity",intensity);
            program.sendUniformFloat("transparency",intensity);
            // mvp = glm::translate(glm::mat4(1.0f), glm::vec3(red, 0.0f, 0.0f));
            mvp *= glm::rotate(glm::mat4(1.0f), glm::radians(deltaTime*10), glm::vec3(1.0f, 1.0f, 1.0f));
            program.sendUniformMat4("mvp", mvp);
            // render
            glClearColor(red, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glPointSize(10.0f);
            glDrawArrays(GL_TRIANGLES,
            0,num_points);
            _window.swapBuffers();
            _window.pollEvents();
        }

        glfwTerminate();
        return 0;
    }

    void Application::animateBackgroundColor(float &red, int &factor, float deltaTime)
    {
        red += (0.08f * deltaTime) * factor;
        if (red > 1.0f || red < 0.0f) factor = factor * -1;
    }

    void Application::processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    std::optional<std::vector<float>> Application::loadObjFile(const char *objFilePath) const
    {
        std::vector<float> vertices;

        //Loads OBJ file from path
        std::ifstream file;
        file.open(objFilePath);
        if (!file.good())
        {
            std::cout << "Can't open obj file " << objFilePath << std::endl;
            return std::nullopt;
        }
        else{
            std::cout << "Abriuuu";
        }

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
        return vertices;
    }
} // namespace core
