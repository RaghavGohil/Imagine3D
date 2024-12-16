#pragma once
#include <glad/glad.h>
#include <string>
#include <iostream>
#include "stb_image.h"
  
class Texture 
{
public:
    // the program ID
    unsigned int ID;
    // constructor reads and builds the texture 
    Texture(const char* path);
    // activate/deactivate the texture 
    void bind() const;
    void unbind() const;  
};