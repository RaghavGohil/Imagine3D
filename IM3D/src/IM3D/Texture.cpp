#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION // define the implemenation code here....
#include "stb_image.h"

Texture::Texture()
{
    this->path = path;
}

unsigned int Texture::load(std::string path, std::string directory, bool gamma){
    std::string filename = std::string(path);
    std::cout << filename.c_str() << std::endl;

    glGenTextures(1, &ID); // Generate the texture ID

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0); // Load the image
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED; // Single channel grayscale
        else if (nrComponents == 3)
            format = GL_RGB; // RGB image
        else if (nrComponents == 4)
            format = GL_RGBA; // RGBA image
        else
            format = GL_RGB; // Default fallback (use RGB for unknown formats)

        glBindTexture(GL_TEXTURE_2D, ID);

        // Set texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Upload the texture data to OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        // Generate mipmaps for the texture if necessary
        if (format != GL_RED) {
            glGenerateMipmap(GL_TEXTURE_2D); // Mipmap generation for RGB and RGBA
        }

        stbi_image_free(data); // Free the loaded image data
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data); // Ensure to free memory if loading fails
    }
    return ID;
}