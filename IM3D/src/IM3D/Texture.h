#pragma once
#include <glad/glad.h>
#include <string>
#include <iostream>
  
class Texture 
{
public:
    // the program ID
    unsigned int ID;
    std::string type;
    std::string path;
    // constructor reads and builds the texture 
    Texture();
    // activate/deactivate the texture 
    unsigned int load(std::string path, std::string directory, bool gamma);
};