#pragma once
#include<glad/glad.h>
#include <vector>

#include <string>
namespace graphics
{
    namespace texture
    {
        class Texture
        {
            public:
                Texture(const std::string &textureFile);
                ~Texture();
                GLuint getID();
                void bind();
                void unbind();

                void sendImageData();

                enum
                {
                    BI_LINEAR = GL_LINEAR,
                    MIPMAPPING = GL_LINEAR_MIPMAP_LINEAR
                };

                int filterMode = MIPMAPPING;
            private:    
                void generateTexture();
                void setTextureParameters();
                void generateMipmapLevels();
                void loadTextureFile();
            private:
                std::string _textureFilePath;
                GLuint _ID;

                int _imageWidth;
                int _imageHeight;
                int _nrChannels;
                unsigned char *_imageData;
        };
    } // namespace texture
    
} // namespace graphics
