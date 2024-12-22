#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
#include "texture.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

// globals
int windowWidth = 800;
int windowHeight = 600;

// timing
double deltaTime = 0.0f;
double currentTime = 0.0f;
double lastTime = 0.0f;

//Camera
Camera* camera = new Camera();


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
    std::cout << windowWidth << " " << windowHeight << std::endl;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
    else
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(camera)
        camera->look(xpos, ypos); 
} 

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Set OpenGL version and profile 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "No this is not minecraft", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Set viewport and resize callback
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Create a camera
    camera->initlialize(window);

    float vertices[] = {
        // Positions            // UVs      // Normals
        // Front face
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,    1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,  0.0f,  0.0f, -1.0f,

        // Back face
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,  0.0f,  0.0f,  1.0f,

        // Left face
        -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,    1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

        // Right face
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,    0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

        // Bottom face
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,    1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

        // Top face
        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,  0.0f,  1.0f,  0.0f
    };


    //unsigned int indices[] = {  // note that we start from 0!
    //    0, 1, 3,   // first triangle
    //    1, 2, 3    // second triangle
    //};   

    // Generate VBO, VAO and EBO
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    //Bind VA0 and set data and apply operations and then unbind
    glBindVertexArray(VAO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    //Enable for drawing
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5*sizeof(float)));
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    //Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // we only need to bind to the VBO, the container's VBO's data already contains the data.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // set the vertex attribute 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Bind the texture
    Texture *texture = new Texture("dirt_actual.png");
    // Create and compile vertex shader
    Shader *shader = new Shader("shaders/def.vert","shaders/lit_spot.frag");
    Shader *lightShader = new Shader("shaders/light.vert","shaders/light.frag");

    glEnable(GL_DEPTH_TEST);

    //light
    float lightAngle = 0.0f;
    float lightX = 0.0f;
    float lightRotSpeed = 30.0f;
    float lightMoveSpeed = 0.2f;

    // Render loop
    while (!glfwWindowShouldClose(window)) {

        currentTime = glfwGetTime(); // gets the current time
        deltaTime = currentTime - lastTime;
        // Input handling
        processInput(window);

        camera->update(deltaTime); 
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 lightModel = glm::mat4(1.0);
        lightAngle += lightRotSpeed * (float) deltaTime;
        lightX += lightMoveSpeed * (float) deltaTime;
        lightModel = glm::translate(lightModel,glm::vec3(lightX,2.0f,2.0f));
        lightShader->use();                 
        lightShader->setMat4("model",lightModel);
        lightShader->setMat4("view",camera->view);
        lightShader->setMat4("projection",camera->projection);
        glBindVertexArray(lightVAO);        
        glDrawArrays(GL_TRIANGLES,0,36);

        // 2. Render the textured object
        shader->use();                      
        glActiveTexture(GL_TEXTURE0);       
        texture->bind();                    
        shader->setSampler2D("texture", 0); 
        shader->setMat4("model",camera->model);
        shader->setVec3("lightPos",lightModel[3]);
        shader->setMat4("view",camera->view);
        shader->setVec3("viewPos",camera->position);
        shader->setVec3("front",camera->front);
        shader->setMat4("projection",camera->projection);
        glBindVertexArray(VAO);             
        glDrawArrays(GL_TRIANGLES,0,36);

        // Swap buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();
        lastTime = currentTime; // gets the delta
    }

    // Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}
