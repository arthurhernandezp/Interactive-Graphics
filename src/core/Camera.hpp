#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "graphics/renderer/ShaderProgram.hpp"

namespace core
{
    class Camera
    {
        enum{
            PERSPECTIVEPROJECTION,
            ORTOGRAPHICPROJECTION
        };
        public:
            Camera(int width, int height, glm::vec3 position);
            void Matrix(float FOVdeg, float nearPlane, float farPlane, glm::mat4 &view,glm::mat4 &projection);
            void Inputs(GLFWwindow* window, float deltaTime);
        private:

        private:
            glm::vec3 _orientation = glm::vec3(0.0f,0.0f,-1.0f);
            glm::vec3 _up = glm::vec3(0.0f,1.0f,0.0f);

            bool _firstClick = true;
            bool _firstRightbuttonClick = false;
            int _width;
            int _height;
            glm::vec3 position;
            float _speed = 0.05f;
            float sensitivity = 100.0f;
            int _projectionType = Camera::PERSPECTIVEPROJECTION;
    };
} // namespace core
