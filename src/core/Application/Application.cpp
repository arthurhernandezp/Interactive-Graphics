#include "Application.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>     //glm::mat4 identity = glm::mat4(1.0f);
#include <glm/gtc/type_ptr.hpp>             //glm::value_ptr

namespace core {

    Application::Application(): _window(800, 600, "LearnOpenGL") {}

    int Application::run()
    {
        std::cout << "glfw version: " << glfwGetVersionString() << '\n';
        // glfw: initialize and configure
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if (!_window.create()) {
            glfwTerminate();
            return -1;
        }
        float red = 0.0f;
        int factor = 1;

        const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 pos;\n"
        "uniform mat4 mvp;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = mvp* vec4(pos, 1);\n"
        "}\0";

        const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "   color = vec4(0.0f, 1.0f, 1.0f, 1.0f);\n"
        "}\n\0";

        GLuint program = glCreateProgram();
        //Compilando o vertex shader
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vs,1,&vertexShaderSource,NULL);
        glCompileShader(vs);
        GLint success;
        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar InfoLog[1024];
            glGetShaderInfoLog(vs, sizeof(InfoLog), NULL, InfoLog);
            fprintf(stderr, "Error compiling shader type %d: '%s'\n", GL_VERTEX_SHADER, InfoLog);
        }
        std::cout << "Compilando Vertex Shader" << std::endl;
        glAttachShader(program,vs);

        //Compilando o fragment shader
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs,1,&fragmentShaderSource,NULL);
        glCompileShader(fs);
        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar InfoLog[1024];
            glGetShaderInfoLog(fs, sizeof(InfoLog), NULL, InfoLog);
            fprintf(stderr, "Error compiling shader type %d: '%s'\n", GL_FRAGMENT_SHADER, InfoLog);
        }
        std::cout << "Compilando Fragment Shader" << std::endl;

        glAttachShader(program,fs);

        //Linkando os shaders com o program
        glLinkProgram(program);


        // Defina a matriz identidade (4x4)
        glm::mat4 mvp = glm::mat4(1.0f);

        glUseProgram(program);

        // Envie a matriz MVP para o shader
        std::cout << "Enviando a matriz MVP para o shader" << std::endl;        
        GLint mvpLoc = glGetUniformLocation(program, "mvp");
        if (mvpLoc != -1) {
            glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
        } else {
            std::cerr << "Uniform 'mvp' não encontrado!" << std::endl;
        }

        std::cout << "Linkando os shaders com o program" << std::endl;
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
