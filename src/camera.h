#pragma once
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera 
{
public:
    Camera();
    ~Camera();

    //Camera settings
    float fov = 45.0f;
    float speed = 2.5f;
    float sensitivity = 0.1f;
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, -90.0f, 0.0f); // pitch, yaw, roll (x,y,z)
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f); // pitch, yaw, roll (x,y,z)
    glm::mat4 view, projection, model;
 
    void initlialize(GLFWwindow* window); // Process input
    void update(double deltaTime); // Process input
    void look(double xpos, double ypos); // For usage in mouse callback

private:

    GLFWwindow* window;
    double deltaTime = 0.0f;

    //mouse
    bool firstMouse = false;
    double lastX = 0.0f;
    double lastY = 0.0f;
    void move();
};