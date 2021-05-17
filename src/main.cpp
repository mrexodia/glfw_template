// Based on: https://blog.conan.io/2019/06/26/An-introduction-to-the-Dear-ImGui-library.html

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return 1;
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
    glfwMakeContextCurrent(window);

    glewInit();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    bool show_test_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImColor(114, 144, 154);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Show demo window
        ImGui::ShowDemoWindow();

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}