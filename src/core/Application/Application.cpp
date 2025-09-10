#include "Application.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>     //glm::mat4 identity = glm::mat4(1.0f);
#include <glm/gtc/type_ptr.hpp>             //glm::value_ptr

#include "graphics/renderer/Shader.hpp"
#include "graphics/renderer/VertexBuffer.hpp"
#include "graphics/renderer/VertexArray.hpp"
#include "graphics/renderer/ShaderProgram.hpp"

#include "core/Camera.hpp"

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

        // Carrega os shaders a partir de um arquivo externo, compila e linka com o programa
        graphics::renderer::ShaderProgram program("shaders/shader.vert","shaders/shader.frag");

        // Carrega os dados a partir de um .obj e salva no std::vector<float> _positions
        loadObjFile(_positions,"resources/teapot.obj");

        //Criar o VAO
        graphics::renderer::VertexArrayObject vao;
        vao.bindBuffer();

        // Colocar os dados no buffer(VBO)
        graphics::renderer::VertexBufferObject vbo;

        // Copia os dados que estão em memoria da CPU para a GPU
        vbo.receiveData(_positions,GL_STATIC_DRAW);

        // Irá linkar o VBO ao VAO e dizer como o opengl deve interpretar os dados e associe ao layout que foi criado o atributo pos
        GLuint pos = program.getAttribLocation("pos");
        vao.LinkVBO(vbo,pos);

        // Unbind all to prevent accidentally modifying them
        vao.unbindBuffer();
        vbo.unbindBuffer();

        float intensity = 1.0f;
        float transparency = 1.0f;

        [[maybe_unused]]auto num_points = _positions.size();
        float lastFrameStartTime = 0.0f;
        float red= 0.0f;
        [[maybe_unused]] int factor = 1;

        // program.sendUniformMat4("mvp",mvp);
        program.sendUniformFloat("intensity",intensity);
        program.sendUniformFloat("transparency",transparency);
        // float rotation = 0.0f;
        // double prevTime = glfwGetTime();
        std::cout << "Numero de vertices: " << _positions.size() << std:: endl;

        auto windowDimensions = _window.getWindowDimensions();
        Camera camera(windowDimensions.first,windowDimensions.second,glm::vec3(0.0f,0.0f,2.0f));

        glEnable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // render loop
        while (!_window.shouldClose())
        {
            // render
            glClearColor(red, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            program.use();
            vao.bindBuffer();

             [[maybe_unused]] auto deltaTime = calculateDeltaTime(lastFrameStartTime);
            // _window.animateBackgroundColor(red, factor, deltaTime);
            camera.Matrix(45.0f,0.1f,100.0f,program,"camMatrix");

            // intensity -= (0.08f * deltaTime) * factor;
            program.sendUniformFloat("intensity",intensity);
            program.sendUniformFloat("transparency",intensity);

            glPointSize(1.5f);
            glDrawArrays(GL_POINTS, 0,num_points);

            _window.swapBuffers();
            _window.pollEvents();
            _window.processInput();
            camera.Inputs(_window.getGLFWwindow());
            program.recompileShaders(_window.getGLFWwindow());
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
            std::vector<int> triangleMesh;
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
            if(text == "f")
            {
                std::vector<std::string> linha;
                std::string comb;
                file >> comb;
                linha.emplace_back(comb);
                file >> comb;
                linha.emplace_back(comb);
                
                file >> comb;
                linha.emplace_back(comb);

                if(!comb.find('\n'))
                {
                    file >> comb;
                    linha.emplace_back(comb);
                }
                    

                for (auto p : linha)
                {
                    size_t slashPos = p.find('/');
                    std::string firstPart = p.substr(0, slashPos);

                    int vertexIndex = std::stoi(firstPart);
                    triangleMesh.push_back(vertexIndex);
                }
                triangleMesh.shrink_to_fit();
                // std::cout << "triangle mesh size: " << triangleMesh.size() << '\n';
                
            }
        }
    }

    float Application::calculateDeltaTime(float &lastFrameStartTime)
    {
            float currentFrameStartTime = static_cast<float>(glfwGetTime());
            float deltaTime = currentFrameStartTime - lastFrameStartTime;
            lastFrameStartTime = currentFrameStartTime;
            return deltaTime;
    }
} // namespace core
