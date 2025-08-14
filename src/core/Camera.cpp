#include "Camera.hpp"
#include <iostream>
namespace core
{
    Camera::Camera(int width, int height, glm::vec3 position)
    : width{width}, height{height}, position{position}
    {

    }

    void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, graphics::renderer::ShaderProgram &program, const char *uniform)
    {
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        view = glm::lookAt(position, position + orientation, up);
        projection = glm::perspective(glm::radians(FOVdeg), float(width/height),nearPlane, farPlane);

        // program.sendUniformMat4(uniform,projection*view);
        glUniformMatrix4fv(glGetUniformLocation(program.getProgramId(),uniform),1,GL_FALSE,glm::value_ptr(projection*view));
    }

    void Camera::Inputs(GLFWwindow *window)
    {
        // Handles key inputs
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            position += speed * orientation;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            position += speed * -glm::normalize(glm::cross(orientation, up));
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            position += speed * -orientation;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            position += speed * glm::normalize(glm::cross(orientation, up));
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            position += speed * up;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            position += speed * -up;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            speed = 0.4f;
        }
        else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        {
            speed = 0.1f;
        }
    }

} // namespace core
