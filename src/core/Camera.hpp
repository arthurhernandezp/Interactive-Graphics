#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// #include <glm/gtx/rotate_vector.hpp>
// #include <glm/gtx/vector_angle.hpp>

#include "graphics/renderer/ShaderProgram.hpp"

namespace core
{
    class Camera
    {
        public:

            Camera(int width, int height, glm::vec3 position);

            void Matrix(float FOVdeg, float nearPlane, float farPlane, graphics::renderer::ShaderProgram &program, const char* uniform);
            void Inputs(GLFWwindow* window);
            glm::vec3 orientation = glm::vec3(0.0f,0.0f,-1.0f);
            glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f);

            int width;
            int height;
            glm::vec3 position;

            float speed = 0.1f;
            float sensitivity = 100.0f;
        private:

        private:
    };
} // namespace core

