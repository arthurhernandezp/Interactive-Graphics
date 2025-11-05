#pragma once
#include "graphics/texture/Texture.hpp"
#include <memory>

namespace graphics
{
    namespace renderer { class ShaderProgram; }
    namespace texture { class Texture; }
    
    namespace material
    {
        class Material
        {
            public:
                Material(std::string textureFilePath);
                void applyTo(std::shared_ptr<renderer::ShaderProgram> prog);
            private:

            private:
                std::shared_ptr<texture::Texture> texture;
        };
    } // namespace material
    
} // namespace graphics
