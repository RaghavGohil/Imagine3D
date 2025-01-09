#pragma once
#include "stb_image.h"
#include <iostream>
#include <glad/glad.h>
#include <vector>
#include "shader.h"

class Skybox{
public:
    Skybox(std::vector<std::string> faces); 
    unsigned int ID;
    void bind() const;
    void unbind() const;
};