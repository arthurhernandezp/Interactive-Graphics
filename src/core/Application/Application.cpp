#include "Application.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>     //glm::mat4 identity = glm::mat4(1.0f);
#include <glm/gtc/type_ptr.hpp>             //glm::value_ptr
#include "graphics/renderer/Shader.hpp"
namespace core 
{
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
        
        float red = 0.0f;
        int factor = 1;

        GLuint program = glCreateProgram();
        
        //Compilando o vertex shader
        try
        {
            graphics::renderer::Shader vertex_shader("shaders/shader.vert",GL_VERTEX_SHADER);
            glAttachShader(program,vertex_shader.getShaderId());
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

        //Compilando o fragment shader        
        try
        {
            graphics::renderer::Shader fragment_shader("shaders/shader.frag",GL_FRAGMENT_SHADER);
            glAttachShader(program,fragment_shader.getShaderId());
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
       
        //Linkando os shaders com o program
        glLinkProgram(program);

        // Defina a matriz identidade (4x4)
        glm::mat4 mvp = glm::mat4(1.0f);

        glUseProgram(program);

        // Envie a matriz MVP para o shader
        std::cout << "Enviando a matriz MVP para o shader" << std::endl;        
        GLint mvpLoc = glGetUniformLocation(program, "mvp");
        if (mvpLoc != -1) 
        {
            glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
        } else
        {
            std::cerr << "Uniform 'mvp' não encontrado!" << std::endl;
        }

        //Criando dados

        float positions[] =
        {
            0.8f,0.4f,0.0f,
            0.8f,-0.4f,0.0f,
            -0.8f,0.4f,0.0f,
            -0.8f,-0.4f,0.0f,
            0.3f,0.2f,0.0f,
            -0.3f,-0.2f,0.0f
        };

        //Criar o VAO
        GLuint vao;
        glGenVertexArrays(1,&vao);
        glBindVertexArray(vao);
        std::cout << "Criando VAO" << '\n';

        //Colocar os dados no buffer(VBO)
        GLuint vbo;
        glGenBuffers(1,&vbo);
        glBindBuffer(GL_ARRAY_BUFFER,vbo);
        glBufferData(GL_ARRAY_BUFFER,
                    sizeof(positions),
                    positions,
                    GL_STATIC_DRAW);
        std::cout << "Criando VBO e colocando os dados de positions no buffer" << '\n';

        //Enviar os dados para o vertex shader
        GLuint pos = glGetAttribLocation(program,"pos");
        std::cout << "Encontrou o pos" << std::endl;
        glEnableVertexAttribArray(pos);
        glVertexAttribPointer(
            pos,3,GL_FLOAT,
            GL_FALSE,0,(void*)0
        );
        std::cout << "Enviando os dados do VBO para o Vertex Shader" << '\n';
        auto num_points = sizeof(positions)/sizeof(float)/3;
        // render loop
        while (!_window.shouldClose())
        {
            processInput(_window.getGLFWwindow());

            animateBackgroundColor(red, factor);

            // render
            glClearColor(red, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glPointSize(10.0f);
            glDrawArrays(GL_POINTS,
            0,num_points);
            _window.swapBuffers();
            _window.pollEvents();
        }

        glfwTerminate();
        return 0;
    }

    void Application::animateBackgroundColor(float &red, int &factor)
    {
            red += 0.00008f * factor;
            if (red > 1.0f || red < 0.0f) factor = factor * -1;
    }

    void Application::processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
} // namespace core
