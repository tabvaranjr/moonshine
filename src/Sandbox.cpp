#include "Sandbox.h"

#include <epoxy/gl.h>
#include <GLFW/glfw3.h>
#include <fmt/format.h>
#include <stdexcept>

namespace Moonshine
{

Sandbox::Sandbox() :
    window(nullptr)
{
    glfwSetErrorCallback([](int error, const char* description) { fmt::print("Error {0:#x}: {1}\n", error, description); } );

    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 800, "Moonshine", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create a window with GLFW");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    fmt::print("Vendor: {0}\n", glGetString(GL_VENDOR));
    fmt::print("Renderer: {0}\n", glGetString(GL_RENDERER));
    fmt::print("Version: {0}\n", glGetString(GL_VERSION));

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    });

    while (true)
    {
        if (glfwWindowShouldClose(window))
        {
            break;
        }

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
}

Sandbox::~Sandbox()
{
    glfwTerminate();
}

}
