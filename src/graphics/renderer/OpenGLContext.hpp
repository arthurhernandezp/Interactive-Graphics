#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace graphics
{
    namespace renderer
    {
        class OpenGLContext
        {
            public:
                OpenGLContext(int openglVersionMajor, int openglVersionMinor, int openglProfile);

                void init();
            private:
                int _OPENGL_VERSION_MAJOR;
                int _OPENGL_VERSION_MINOR;
                int _OPENGL_PROFILE;
        };
    } // namespace renderer
    
} // namespace graphcis
