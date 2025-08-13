#include "WindowFramework.hpp"

namespace graphics
{
    Window::Window(unsigned int width, unsigned int height, const char* title)
        : _width(width), _height(height), _title(title), _window(nullptr) {}

    bool Window::create()
    {
        _window = glfwCreateWindow(_width, _height, _title, nullptr, nullptr);
        if (!_window)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            return false;
        }

        glfwMakeContextCurrent(_window);
        glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return false;
        }

        return true;
    }

    void Window::swapBuffers()
    {
        glfwSwapBuffers(_window);
    }

    void Window::pollEvents()
    {
        glfwPollEvents();
    }

    void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    float Window::getAspectRatio() const
    {
        return _width/_height;
    }

    std::pair<unsigned int, unsigned int> Window::getWindowDimensions() const
    {
        return std::make_pair(_width,_height);
    }

    GLFWwindow* Window::getGLFWwindow() const
    {
        return _window;
    }

    bool Window::shouldClose() const
    {
        return glfwWindowShouldClose(_window);
    }

    void Window::animateBackgroundColor(float &red, int &factor, float deltaTime)
    {
        red += (0.08f * deltaTime) * factor;
        if (red > 1.0f || red < 0.0f) factor = factor * -1;
    }

    void Window::processInput()
    {
        if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(_window, true);
    }
}// namespace graphics
