#include "Sandbox.h"

#include <epoxy/gl.h>
#include <GLFW/glfw3.h>
#include <fmt/format.h>
#include <stdexcept>

auto APPLICATION_NAME = "Moonshine";

namespace Moonshine
{

Sandbox::Sandbox() :
    Sandbox(Parameters())
{
}

Sandbox::Sandbox(Parameters p) :
    window(nullptr)
{
    glfwSetErrorCallback([](int error, const char* description) { fmt::print("Error {0:#x}: {1}\n", error, description); } );

    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    if (p.IsDebugModeActive)
    {
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (p.IsFullScreen)
    {
        auto monitor = glfwGetPrimaryMonitor();
        auto mode = glfwGetVideoMode(monitor);

        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        window = glfwCreateWindow(mode->width, mode->height, APPLICATION_NAME, monitor, nullptr);
    }
    else
    {
        window = glfwCreateWindow(p.Width, p.Height, APPLICATION_NAME, nullptr, nullptr);
    }

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
