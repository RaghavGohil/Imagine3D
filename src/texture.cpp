#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION // define the implemenation code here....
#include "stb_image.h"

Texture::Texture(const char* path)
{
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* data = stbi_load(path, &width, &height, &nrChannels, STBI_rgb_alpha); 
    glGenTextures(1, &(Texture::ID));
     // set the texture wrapping/filtering options (on the currently bound texture object)
    glBindTexture(GL_TEXTURE_2D, Texture::ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
}

// activate/deactivate the texture 
void Texture::bind() const
{
    // Activate the texture unit
    glBindTexture(GL_TEXTURE_2D, Texture::ID);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}