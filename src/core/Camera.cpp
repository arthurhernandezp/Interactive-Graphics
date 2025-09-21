#include "Camera.hpp"
#include <iostream>
namespace core
{
    Camera::Camera(int _width, int _height, glm::vec3 position)
    : _width{_width}, _height{_height}, position{position}
    {

    }

    void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, glm::mat4 &view , glm::mat4 &projection)
    {
        view = glm::lookAt(position, position + _orientation, _up);

        if(_projectionType == Camera::PERSPECTIVEPROJECTION)
        {
            projection = glm::perspective(glm::radians(FOVdeg), float(_width/_height),nearPlane, farPlane* 100);
        }
        else if (_projectionType == Camera::ORTOGRAPHICPROJECTION)
        {
            [[maybe_unused]]float aspectRatio = static_cast<float>(_width) / static_cast<float>(_height);
            auto side = FOVdeg/10 * aspectRatio;
            projection = glm::ortho(-side, side, -side, side, nearPlane, farPlane * 100);
        }
    }

    void Camera::Inputs(GLFWwindow *window, float deltaTime)
    {
        // Handles key inputs
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            position += _speed * _orientation;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            position += _speed * -glm::normalize(glm::cross(_orientation, _up));
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            position += _speed * -_orientation;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            position += _speed * glm::normalize(glm::cross(_orientation, _up));
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            position += _speed * _up;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            position += _speed * -_up;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            _speed = deltaTime * 10 * 2;
        }
        else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        {
            _speed = deltaTime * 10;
        }

        if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            // Hides mouse cursor
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            // Prevents camera from jumping on the first click
            if (_firstClick)
            {
                glfwSetCursorPos(window, (_width / 2), (_height / 2));
                _firstClick = false;
            }

            // Stores the coordinates of the cursor
            double mouseX;
            double mouseY;
            // Fetches the coordinates of the cursor
            glfwGetCursorPos(window, &mouseX, &mouseY);

            // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
            // and then "transforms" them into degrees
            float rotX = sensitivity * (float)(mouseY - (_height / 2)) / _height;
            float rotY = sensitivity * (float)(mouseX - (_width / 2)) / _width;

            // Calculates _upcoming vertical change in the _orientation
            glm::vec3 new_orientation = glm::rotate(_orientation, glm::radians(-rotX), glm::normalize(glm::cross(_orientation, _up)));

            // Decides whether or not the next vertical _orientation is legal or not
            if (abs(glm::angle(new_orientation, _up) - glm::radians(90.0f)) <= glm::radians(85.0f))
            {
                _orientation = new_orientation;
            }

            // Rotates the _orientation left and right
            _orientation = glm::rotate(_orientation, glm::radians(-rotY), _up);

            // Sets mouse cursor to the middle of the screen so that it doesn't end _up roaming around
            glfwSetCursorPos(window, (_width / 2), (_height / 2));
        }


        if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
            _firstClick = true;
        }


        if (glfwGetKey(window, GLFW_KEY_F7) == GLFW_PRESS)
        {
            _firstRightbuttonClick = true;
        }
        else if (glfwGetKey(window, GLFW_KEY_F7) == GLFW_RELEASE && _firstRightbuttonClick)
        {
            _firstRightbuttonClick = false;
            if(_projectionType == Camera::PERSPECTIVEPROJECTION)
            {
                _projectionType = Camera::ORTOGRAPHICPROJECTION;
            }
            else if(_projectionType == Camera::ORTOGRAPHICPROJECTION)
            {
                _projectionType = Camera::PERSPECTIVEPROJECTION;
            }
        }
    }
} // namespace core
