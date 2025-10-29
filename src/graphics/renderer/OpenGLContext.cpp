#include "OpenGLContext.hpp"

namespace graphics
{
    namespace renderer
    {
        OpenGLContext::OpenGLContext(int openglVersionMajor, int openglVersionMinor, int openglProfile)
        :  _OPENGL_VERSION_MAJOR{openglVersionMajor}, _OPENGL_VERSION_MINOR{openglVersionMinor}, _OPENGL_PROFILE{openglProfile}
        {
            init();
        }

        OpenGLContext::~OpenGLContext()
        {
        }

        void OpenGLContext::init() 
        {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _OPENGL_VERSION_MAJOR);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _OPENGL_VERSION_MINOR);
            glfwWindowHint(GLFW_OPENGL_PROFILE, _OPENGL_PROFILE);
        };
    } // namespace renderer
    
} // namespace graphcis
