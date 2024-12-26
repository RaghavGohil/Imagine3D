#pragma once
#include "mesh.h" 
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model 
{
    public:
        Model(char *path)
        {
            loadModel(path);
        }
        void draw(Shader &shader);	
    private:
        // model data
        std::vector<Mesh> meshes;
        std::string directory;
        std::vector<Texture> textures_loaded; 
    

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene, glm::mat4 parentTransform);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};