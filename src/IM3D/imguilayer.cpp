#include "imguilayer.h"
#include <iostream>
#include <GLFW/glfw3.h>   // Make sure GLFW is included

ImGuiLayer::ImGuiLayer(GLFWwindow* window) : window(window)
{

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.Fonts->AddFontDefault();  // Ensure that a default font is loaded

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);   // Install GLFW callbacks
    ImGui_ImplOpenGL3_Init();  // OpenGL backend initialization

}

ImGuiLayer::~ImGuiLayer()
{

    // Clean up ImGui and OpenGL backend
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

}

void ImGuiLayer::BeginFrame() const
{

    // Start a new ImGui frame
    ImGui_ImplOpenGL3_NewFrame();   // OpenGL backend frame start
    ImGui_ImplGlfw_NewFrame();      // GLFW backend frame start
    ImGui::NewFrame();              // New ImGui frame

}

void ImGuiLayer::EndFrame() const
{

    // Render ImGui content
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}


// Function to render an OpenGL texture to an ImGui window
void ImGuiLayer::renderTextureToImGuiWindow(unsigned int &textureID) const
{

    // Get window size and set ImGui display size
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)windowWidth, (float)windowHeight);

    // Begin the ImGui window and render the texture
    ImGui::Begin("GameWindow");
    {
        // Render the OpenGL texture in the window (you may need to adjust the size of the ImVec2)
        ImGui::Image((ImTextureID)textureID, ImVec2(400, 400)); // Render texture with size
    }
    ImGui::End();

}
