#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace graphics {

class Window {
public:
    Window(unsigned int width, unsigned int height, const char* title);

    bool create();
    void swapBuffers();
    void pollEvents();
    bool shouldClose() const;
    void animateBackgroundColor(float &red, int &factor, float deltaTime);
    void processInput();
    GLFWwindow* getGLFWwindow() const;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

private:
    unsigned int _width, _height;
    const char* _title;
    GLFWwindow* _window;
};

} // namespace graphics
