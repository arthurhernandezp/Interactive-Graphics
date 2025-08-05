#include "Application.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>     //glm::mat4 identity = glm::mat4(1.0f);
#include <glm/gtc/type_ptr.hpp>             //glm::value_ptr
#include "graphics/renderer/Shader.hpp"
#include "graphics/renderer/VertexBuffer.hpp"
#include "graphics/renderer/ShaderProgram.hpp"

#include <memory>       // unique_ptr
#include <fstream>      // read obj file

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

        graphics::renderer::ShaderProgram program("shaders/shader.vert","shaders/shader.frag");

        program.use();

        // Defina a matriz identidade (4x4)
        glm::mat4 mvp = glm::mat4(1.0f);
        // Envie a matriz MVP para o shader

        std::cout << "Enviando a matriz MVP para o shader" << std::endl;
        program.sendUniformMat4("mvp",mvp);
        program.sendUniformFloat("intensity",0.5f);
        program.sendUniformFloat("transparency",0.2f);
        
        //Criar o VAO
        GLuint vao;
        glGenVertexArrays(1,&vao);
        glBindVertexArray(vao);
        std::cout << "Criando VAO" << '\n';

        //Colocar os dados no buffer(VBO)
        graphics::renderer::VertexBufferObject vbo;
        vbo.bindBuffer();
        //Receber dados de positions
        glBufferData(GL_ARRAY_BUFFER,_positions.size() * sizeof(GLfloat), &_positions[0],GL_STATIC_DRAW);
        // vbo.receiveData(positionsF,sizeof(positionsF),GL_STATIC_DRAW);
        GLuint pos = program.getAttribLocation("pos");
        //Enviar os dados para o vertex shader
        vbo.sendData(pos,3,GL_FLOAT);

        float colors[] =
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
        vbo2.receiveData(colors,sizeof(colors),GL_STATIC_READ);

        GLuint clrLocation = program.getAttribLocation("clr");
        vbo2.sendData(clrLocation,3,GL_FLOAT);

        auto num_points = _positions.size();
        float lastFrameStartTime = 0.0f;
        float red= 0.0f;
        float intensity = 1.0f;
        int factor = 1;
        // render loop
        while (!_window.shouldClose())
        {
            glBindVertexArray(vao);

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

    bool Application::loadObjFile(const char *objFilePath) const
    {
        return false;
    }
} // namespace core
