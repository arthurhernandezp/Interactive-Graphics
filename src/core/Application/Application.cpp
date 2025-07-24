#include "Application.hpp"

namespace core {

    Application::Application(): m_window(800, 600, "LearnOpenGL") {}

    int Application::run()
    {
        // glfw: initialize and configure
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if (!m_window.create()) {
            glfwTerminate();
            return -1;
        }

        // render loop
        while (!m_window.shouldClose()) {
            processInput(m_window.getGLFWwindow());

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_window.swapBuffers();
            m_window.pollEvents();
        }

        glfwTerminate();
        return 0;
    }

    void Application::changeBackgroundColor()
    {
        std::cout << "Change background color functionality is not implemented yet." << std::endl;
    }

    void Application::processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }


} // namespace core
