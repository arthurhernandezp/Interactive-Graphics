#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

namespace graphics
{
    namespace texture
    {
        Texture::Texture(const std::string &textureFile) : _textureFilePath{textureFile}
        {
            generateTexture();
            bind();
            setTextureParameters();
            loadTextureFile();
            if (_imageData)
            {
                std::cout << "Texture: " << _textureFilePath << " loaded!" << '\n';
                sendImageData();
                if(filterMode == MIPMAPPING)
                    generateMipmapLevels();
                
                stbi_image_free(_imageData);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }
        }

        Texture::~Texture()
        {
            glDeleteTextures(1, &_ID);
        }

        GLuint Texture::getID()
        {
            return _ID;
        }

        void Texture::bind()
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D,_ID);
        }

        void Texture::unbind()
        {
            glBindTexture(GL_TEXTURE_2D,0);
        }

        void Texture::sendImageData()
        {
            GLenum format = (_nrChannels == 4) ? GL_RGBA : GL_RGB;
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                format,
                _imageWidth,
                _imageHeight,
                0,
                format,
                GL_UNSIGNED_BYTE,
                _imageData
            );
        }

        void Texture::generateTexture()
        {
            glGenTextures(1,&_ID);
        }

        void Texture::setTextureParameters()
        {
            //Filter parameters
            // Minification filter: Quando está distante da superficie
            glTexParameteri(
                GL_TEXTURE_2D,
                GL_TEXTURE_MIN_FILTER,
                filterMode
            );
            // Magnificagtion filter: Quando está proximo a superficie e os texels se tornam grandes as vezes maiores que o pixel
            // nesse caso será usado Bi-linear filtering
            glTexParameteri(
                GL_TEXTURE_2D,
                GL_TEXTURE_MAG_FILTER,
                GL_LINEAR
            );

            // WRAP IN S AND T DIRECTION IF TEXTURE IS OUTSIDE OF THE st-texture (0-1)
            glTexParameteri(
                GL_TEXTURE_2D,
                GL_TEXTURE_WRAP_S,
                GL_REPEAT
            );

            glTexParameteri(
                GL_TEXTURE_2D,
                GL_TEXTURE_WRAP_T,
                GL_REPEAT
            );
        }

        void Texture::generateMipmapLevels()
        {
            glGenerateMipmap( GL_TEXTURE_2D );
        }

        void Texture::loadTextureFile()
        {
            _imageData = stbi_load(_textureFilePath.c_str(), &_imageWidth, &_imageHeight, &_nrChannels, 0);
        }

    } // namespace texture
    
} // namespace graphics
