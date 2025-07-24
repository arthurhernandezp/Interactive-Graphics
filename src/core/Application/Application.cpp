#include "Application.hpp"

namespace core {

    Application::Application(): m_window(800, 600, "LearnOpenGL") {}

    int Application::run()
    {
        std::cout << "glfw version: " << glfwGetVersionString() << '\n';
        // glfw: initialize and configure
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        if (!m_window.create()) {
            glfwTerminate();
            return -1;
        }
        float red = 0.0f;
        int factor = 1;
        // render loop
        while (!m_window.shouldClose())
        {
            processInput(m_window.getGLFWwindow());

            animateBackgroundColor(red, factor);

            // render
            glClearColor(red, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_window.swapBuffers();
            m_window.pollEvents();
        }

        glfwTerminate();
        return 0;
    }

    void Application::animateBackgroundColor(float &red, int &factor)
    {
            red += 0.005f * factor;
            if (red > 1.0f || red < 0.0f) factor = factor * -1;
    }

    void Application::processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }


} // namespace core
