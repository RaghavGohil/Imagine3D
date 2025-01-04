#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
#include "skybox.h"
#include "camera.h"
#include "model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

// globals
int windowWidth = 800;
int windowHeight = 600;
unsigned int texColor, rbo;

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
    
    // Reallocate the texture with the new size
    glBindTexture(GL_TEXTURE_2D, texColor);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Reallocate the renderbuffer with the new size
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
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

    float quadVerts[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    }; 

    //FRAMEBUFFER
    unsigned int quadVAO,quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glBindVertexArray(quadVAO);

    glGenBuffers(1, &quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);
    // set the vertex attribute 
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);
    //unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // Create a color attachment texture
    glGenTextures(1, &texColor);
    glBindTexture(GL_TEXTURE_2D, texColor);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColor, 0);

    // Create a renderbuffer object for depth and stencil attachment
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    // Check if the framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }
    
    // Unbind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
  

    Shader *renderTexture = new Shader("shaders/render_texture.vert","shaders/render_texture.frag");

    //Model
    Model* model = new Model("scene.gltf");
    Shader *shader = new Shader("shaders/model.vert","shaders/model.frag");

    //Outline stencil test
    Shader* shaderSingleColor = new Shader("shaders/outline.vert","shaders/outline.frag");

    //Skybox
    Shader* skyboxShader = new Shader("shaders/skybox.vert", "shaders/skybox.frag");

    std::vector<std::string> faces = {
        "cubemap/px.jpg", // Positive X
        "cubemap/nx.jpg", // Negative X
        "cubemap/py.jpg", // Positive Y
        "cubemap/ny.jpg", // Negative Y
        "cubemap/pz.jpg", // Positive Z
        "cubemap/nz.jpg"  // Negative Z 
    };

    Skybox* skybox = new Skybox(faces);

    //light
    float lightAngle = 0.0f;
    float lightRotSpeed = 30.0f;
    Shader *lightShader = new Shader("shaders/light.vert","shaders/light.frag");

    // Generate VBO, VAO and EBO
    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);
    // we only need to bind to the VBO, the container's VBO's data already contains the data.
    glGenBuffers(1, &cubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    // set the vertex attribute 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        currentTime = glfwGetTime(); // Get the current time
        deltaTime = currentTime - lastTime;

        // Input handling
        processInput(window);

        // Update camera
        camera->update(deltaTime);

        // === Render to FBO ===
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glEnable(GL_DEPTH_TEST);  // Enable depth testing for correct depth rendering
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Set background color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // Clear all buffers

        // Render light
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightAngle += lightRotSpeed * static_cast<float>(deltaTime);
        lightModel = glm::translate(lightModel, glm::vec3(0.0f, 2.5f, 0.0f));
        lightModel = glm::rotate(lightModel, glm::radians(lightAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        lightShader->use();
        lightShader->setMat4("model", lightModel);
        lightShader->setMat4("view", camera->view);
        lightShader->setMat4("projection", camera->projection);
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glm::mat4 modelModel = glm::mat4(1.0f);
        shader->use();
        shader->setMat4("model", modelModel);
        shader->setMat4("view", camera->view);
        shader->setMat4("projection", camera->projection);
        glm::vec3 lightWorldPos = glm::vec3(lightModel * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        shader->setVec3("lightPos", lightWorldPos);

        model->draw(*shader);

        glDisable(GL_CULL_FACE);  // Disable face culling (optional based on need)

        // === Render the Skybox ===
        glDepthFunc(GL_LEQUAL);  // Set depth function to allow skybox rendering behind everything else

        glm::mat4 skyboxModel = glm::mat4(1.0f);
        skyboxModel = glm::scale(skyboxModel, glm::vec3(1.0f));  // Scale skybox
        skyboxShader->use();
        skyboxShader->setMat4("model", skyboxModel);
        skyboxShader->setMat4("view", glm::mat4(glm::mat3(camera->view)));  // Remove translation from camera view for skybox
        skyboxShader->setMat4("projection", camera->projection);
        skyboxShader->setInt("skybox", 0);

        skybox->bind(); 
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        skybox->unbind(); 

        glDepthFunc(GL_LESS);  // Reset depth function to default

        // === Render to Default Framebuffer ===
        glBindFramebuffer(GL_FRAMEBUFFER, 0);  // Switch back to default framebuffer
        glDisable(GL_DEPTH_TEST);  // Disable depth testing for screen-space quad rendering

        // Clear default framebuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind texture for rendering
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texColor);

        // Render full-screen quad (post-processing)
        renderTexture->use();  // Use the shader for rendering the full-screen quad
        renderTexture->setSampler2D("screenTexture", 0);  // Bind the texture to the shader
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Unbind resources
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);

        // Swap buffers and poll for events
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Update time
        lastTime = currentTime;
    }
 
 
    // Cleanup
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glfwTerminate();
    return 0;
}
