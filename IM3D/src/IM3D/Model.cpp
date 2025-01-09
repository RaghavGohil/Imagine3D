#include "Model.h"

void Model::draw(Shader &shader)
{
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].draw(shader);
} 

void Model::loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene, glm::mat4(1.0f));
}

void Model::processNode(aiNode *node, const aiScene *scene, glm::mat4 parentTransform)
{
    // Convert Assimp transformation matrix to GLM matrix
    glm::mat4 nodeTransform = glm::transpose(glm::make_mat4(&node->mTransformation.a1));
    glm::mat4 globalTransform = parentTransform * nodeTransform;

    // Process all the node's meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        Mesh processedMesh = processMesh(mesh, scene);
        processedMesh.model = globalTransform; // Save the transformation for the mesh
        meshes.push_back(processedMesh);
    }

    // Process all child nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, globalTransform);
    } 
} 

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    // Data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // Walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // Placeholder vector for conversion from Assimp's vector to glm's vec3

        // Positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        // Normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        // Texture coordinates
        if (mesh->mTextureCoords[0]) // Check if the mesh contains texture coordinates
        {
            glm::vec2 vec;
            // A vertex can contain up to 8 different texture coordinates, but we assume we're using the first set
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
        {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f); // No texture coordinates
        }

        // Tangents and Bitangents
        if (mesh->HasTangentsAndBitangents())
        {
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;

            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        else
        {
            vertex.Tangent = glm::vec3(0.0f, 0.0f, 0.0f); // Default value if tangents are not available
            vertex.Bitangent = glm::vec3(0.0f, 0.0f, 0.0f); // Default value if bitangents are not available
        }

        // Add the vertex to the vertices vector
        vertices.push_back(vertex);
    }

    // Walk through each of the mesh's faces and retrieve the corresponding vertex indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Process materials
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

    // Load textures (diffuse, specular, normal, height)
    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // Return the mesh object created from the extracted mesh data
    return Mesh(vertices, indices, textures);
}


std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
    std::vector<Texture> textures;

    // Loop through all textures of the specified type
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);

        // Check if the texture is already loaded
        std::string texturePath = str.C_Str();
        auto it = std::find_if(textures_loaded.begin(), textures_loaded.end(),
            [&texturePath](const Texture& t) { return t.path == texturePath; });

        if (it != textures_loaded.end()) {
            // Texture already loaded, add it to the list
            textures.push_back(*it);
        } else {
            // Texture not loaded, load it
            Texture texture;
            if (texture.load(texturePath, directory, false)) {
                texture.type = typeName;
                texture.path = texturePath; // Store the texture path
                textures.push_back(texture);
                textures_loaded.push_back(texture); // Add to loaded textures
            } else {
                std::cerr << "Failed to load texture: " << texturePath << std::endl;
            }
        }
    }

    return textures;
}
