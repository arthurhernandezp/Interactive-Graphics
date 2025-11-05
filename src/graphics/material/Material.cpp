#include "Material.hpp"
#include <iostream>
#include "graphics/renderer/ShaderProgram.hpp"

namespace graphics
{
    namespace material
    {
        Material::Material(std::string textureFilePath) 
        {
            texture = std::make_shared<texture::Texture>(textureFilePath);
        }

        void Material::applyTo(std::shared_ptr<renderer::ShaderProgram> prog)
        {
            glActiveTexture(GL_TEXTURE0);
            texture->bind();                //bind texture to GL_TEXTURE0

            prog->use();
            prog->sendUniform("tex",0); 
        }

    } // namespace material

} // namespace graphics
