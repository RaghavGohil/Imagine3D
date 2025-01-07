#pragma once
#include "imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

class ImGuiLayer
{
public:
    ImGuiLayer(GLFWwindow* window);
    ~ImGuiLayer();
    void GLStart() const;
    void GLEnd() const;
    void render() const;
    void renderTextureToImGuiWindow(unsigned int &textureID) const;
private:
    GLFWwindow* window;
};