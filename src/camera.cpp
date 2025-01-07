#include "camera.h"

Camera::Camera(){}
Camera::~Camera(){}

void Camera::initlialize(GLFWwindow* window)
{
    this->window = window;
}

void Camera::look(double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = (float) (xpos - lastX);
    float yoffset = (float) (lastY - ypos); 
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    rotation.y += xoffset; // rotate camera y
    rotation.x += yoffset; // rotate camera x

    if(rotation.x > 89.0f)
        rotation.x = 89.0f;
    if(rotation.x < -89.0f)
        rotation.x = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    direction.y = sin(glm::radians(rotation.x));
    direction.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    front = glm::normalize(direction);
}

void Camera::move()
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += speed * front * (float) deltaTime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= speed * front * (float) deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(front, glm::vec3(0.0f,1.0f,0.0f))) * speed * (float) deltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(front, glm::vec3(0.0f,1.0f,0.0f))) * speed * (float) deltaTime;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        position += speed * glm::vec3(0.0f,1.0f,0.0f) * (float) deltaTime;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        position -= speed * glm::vec3(0.0f,1.0f,0.0f) * (float) deltaTime;
}

void Camera::update(double deltaTime)
{
    this->deltaTime = deltaTime;
    move();
    model = glm::mat4(1.0f);
    int width, height; glfwGetWindowSize(window, &width, &height); 
    float aspect = (float)width/(float)height;
    projection = glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
    view = glm::lookAt( position, position + front , glm::vec3(0.0f,1.0f,0.0f));
}