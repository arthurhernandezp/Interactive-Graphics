#include "Application.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>     //glm::mat4 identity = glm::mat4(1.0f);
#include <glm/gtc/type_ptr.hpp>             //glm::value_ptr

#include "graphics/renderer/Shader.hpp"
#include "graphics/renderer/VertexBuffer.hpp"
#include "graphics/renderer/VertexArray.hpp"
#include "graphics/renderer/ShaderProgram.hpp"
#include "graphics/renderer/ElementBuffer.hpp"

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

        // Carrega os dados a partir de um .obj e salva no std::vector<float> _positions
        loadObjFile(_positions,"resources/teapot.obj");
        triangleIndex.shrink_to_fit();
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
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        std::cout << "Triangular mesh size: " << triangleIndex.size() << '\n';
        graphics::renderer::ElementBufferObject EBO(triangleIndex.data(),triangleIndex.size());
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
            if (glfwGetKey(_window.getGLFWwindow(), GLFW_KEY_P) == GLFW_PRESS)
            {
                if (firstClick)
                {
                    activatePoints = !activatePoints;
                    firstClick = false;
                }
            }
            if (glfwGetKey(_window.getGLFWwindow(), GLFW_KEY_P) == GLFW_RELEASE)
            {
                firstClick = true;
            }

            if(activatePoints)
                glDrawArrays(GL_POINTS, 0,num_points);

            EBO.bindBuffer();
            glDrawElements(GL_TRIANGLES,triangleIndex.size(),GL_UNSIGNED_INT,0);
            _window.swapBuffers();
            _window.pollEvents();
            _window.processInput();
            camera.Inputs(_window.getGLFWwindow());
            program.recompileShaders(_window.getGLFWwindow());
        }

        glfwTerminate();
        return 0;
    }

    void Application::loadObjFile(std::vector<float>& vertices, const char* objFilePath) {
        std::ifstream file(objFilePath);
        if (!file.is_open()) {
            std::cout << "Can't open obj file " << objFilePath << std::endl;
            return;
        }

        vertices.clear();
        triangleIndex.clear(); // Assumindo que triangleIndex é um std::vector<int> membro da classe

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string type;
            iss >> type;

            if (type == "v")
            {
                float x, y, z;
                if (iss >> x >> y >> z) {
                    vertices.push_back(x);
                    vertices.push_back(y);
                    vertices.push_back(z);
                }
            }

            else if (type == "f") {
                std::vector<int> faceIndices;
                std::string vertexData;
                while (iss >> vertexData) {
                    // Extrai o índice do vértice (antes da primeira '/')
                    size_t slashPos = vertexData.find('/');
                    std::string vertexIndexStr = vertexData.substr(0, slashPos);
                    try {
                        int vertexIndex = std::stoi(vertexIndexStr) - 1; // OBJ usa índices base 1
                        faceIndices.push_back(vertexIndex);
                    } catch (const std::exception& e) {
                        std::cout << "Error parsing face index: " << vertexData << std::endl;
                    }
                }

                // Triangulação
                if (faceIndices.size() >= 3) {
                    triangleIndex.push_back(faceIndices[0]);
                    triangleIndex.push_back(faceIndices[1]);
                    triangleIndex.push_back(faceIndices[2]);
                    if (faceIndices.size() == 4) { // face
                        triangleIndex.push_back(faceIndices[0]);
                        triangleIndex.push_back(faceIndices[2]);
                        triangleIndex.push_back(faceIndices[3]);
                    }
                }
            }
        }

        file.close();
        std::cout << "Loaded " << vertices.size() / 3 << " vertices and "
                << triangleIndex.size() / 3 << " triangles from " << objFilePath << std::endl;
    }

    float Application::calculateDeltaTime(float &lastFrameStartTime)
    {
            float currentFrameStartTime = static_cast<float>(glfwGetTime());
            float deltaTime = currentFrameStartTime - lastFrameStartTime;
            lastFrameStartTime = currentFrameStartTime;
            return deltaTime;
    }
} // namespace core
