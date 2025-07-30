#include "Application.hpp"

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

        // const char* vertexShaderSource = "#version 330 core\n"
        // "layout (location = 0) in vec3 pos;\n"
        // "uniform mat4 mvp;\n"
        // "void main()\n"
        // "{\n"
        // "   gl_Position = mvp* vec4(pos, 1);\n"
        // "}\0";

        // const char* fragmentShaderSource = "#version 330 core\n"
        // "out vec4 color;\n"
        // "void main()\n"
        // "{\n"
        // "   color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
        // "}\n\0";

        // GLuint program = glCreateProgram();
        // //Compilando o vertex shader
        // GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        // glShaderSource(vs,1,&vertexShaderSource,NULL);
        // glCompileShader(vs);
        // glAttachShader(program,vs);

        // //Compilando o fragment shader
        // GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        // glShaderSource(fs,1,&fragmentShaderSource,NULL);
        // glCompileShader(fs);
        // glAttachShader(program,fs);

        // //Linkando os shaders com o program
        // glLinkProgram(program);

        // //Criando dados

        // float positions[] =
        // {
        //     -0.8f,0.4f,0.0f,
        //     0.8f,0.4f,0.0f,
        //     0.8f,-0.4f,0.0f,
        //     -0.8f,0.4f,0.0f,
        //     0.8f,-0.4f,0.0f,
        //     -0.8f,-0.4f,0.0f
        // };

        // //Criar o VAO
        // GLuint vao;
        // glGenVertexArrays(1,&vao);
        // glBindVertexArray(vao);

        // //Colocar os dados no buffer(VBO)
        // GLuint buffer;
        // glGenBuffers(1,&buffer);
        // glBindBuffer(GL_ARRAY_BUFFER,buffer);
        // glBufferData(GL_ARRAY_BUFFER,
        //             sizeof(positions),
        //             positions,
        //             GL_STATIC_DRAW);

        // //Enviar os dados para o vertex shader
        // GLuint pos = glGetAttribLocation(program,"pos");
        // glEnableVertexArrayAttrib(pos);
        // glVertexAttribPointer(
        //     pos,3,GL_FLOAT,
        //     GL_FALSE,0,(void*)0
        // );
        
        // render loop
        while (!_window.shouldClose())
        {
            processInput(_window.getGLFWwindow());

            animateBackgroundColor(red, factor);

            // render
            glClearColor(red, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            // glUseProgram(program);
            // glDrawArrays(GL_POINTS,
            // 0,6);
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
