#include "Sandbox.h"

#include <epoxy/gl.h>
#include <GLFW/glfw3.h>
#include <fmt/format.h>
#include <stdexcept>

#include <map>

namespace Moonshine
{

auto APPLICATION_NAME = "Moonshine";

static std::map<GLFWwindow*, std::function<void(int, int)>> sWindowSizeCallbackMap;
static std::map<GLFWwindow*, std::function<void(int, int, int)>> sMouseButtonCallbackMap;
static std::map<GLFWwindow*, std::function<void(int, int, int, int)>> sKeyCallbackMap;

void InternalWindowSizeCallback(GLFWwindow* window, int width, int height);

void InternalKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void InternalMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

Sandbox::Sandbox() :
    Sandbox(Parameters())
{
}

Sandbox::Sandbox(Parameters p) :
        _window(nullptr)
{
    glfwSetErrorCallback([](auto error, auto description) { fmt::print("Error {0:#x}: {1}\n", error, description); } );

    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    try
    {
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

            _window = glfwCreateWindow(mode->width, mode->height, APPLICATION_NAME, monitor, nullptr);
        }
        else
        {
            _window = glfwCreateWindow(p.Width, p.Height, APPLICATION_NAME, nullptr, nullptr);
        }

        if (_window == nullptr)
        {
            throw std::runtime_error("Failed to create a window with GLFW");
        }

        glfwMakeContextCurrent(_window);
        glfwSwapInterval(1);

        if (epoxy_gl_version() < 45 || !epoxy_has_gl_extension("GL_ARB_direct_state_access"))
        {
            throw std::runtime_error("OpenGL 4.5 or the GL_ARB_direct_state_access extension is required to use the sandbox.");
        }

        glfwSetWindowSizeCallback(_window, InternalWindowSizeCallback);
        glfwSetMouseButtonCallback(_window, InternalMouseButtonCallback);
        glfwSetKeyCallback(_window, InternalKeyCallback);

        if (p.IsDebugModeActive)
        {
            if (epoxy_has_gl_extension("GL_KHR_debug"))
            {
                auto glDebugCallback = [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                          const GLchar* message, const GLvoid* userParam)
                {
                    fmt::print("Error {0:#x}: {1}\n", id, message);
                };

                glDebugMessageCallback(glDebugCallback, nullptr);
                glEnable(GL_DEBUG_OUTPUT);
            }
            else
            {
                fmt::print("Missing GL_KHR_debug extension support for debug output\n");
            }
        }
    }
    catch (...)
    {
        glfwTerminate();
        throw;
    }
}

void Sandbox::printRendererInformation() const
{
    fmt::print("Vendor: {0}\n", glGetString(GL_VENDOR));
    fmt::print("Renderer: {0}\n", glGetString(GL_RENDERER));
    fmt::print("Version: {0}\n", glGetString(GL_VERSION));
}

Sandbox::~Sandbox()
{
    glfwTerminate();
}

void Sandbox::run() const
{
    while (true)
    {
        if (glfwWindowShouldClose(_window))
        {
            break;
        }

        glfwPollEvents();
    }

    glfwDestroyWindow(_window);
}

void Sandbox::setWindowSizeCallback(std::function<void(int, int)> callback)
{
    sWindowSizeCallbackMap[_window] = callback;
}

void Sandbox::setKeyCallback(std::function<void(int, int, int, int)> callback)
{
    sKeyCallbackMap[_window] = callback;
}

void Sandbox::setMouseButtonCallback(std::function<void(int, int, int)> callback)
{
    sMouseButtonCallbackMap[_window] = callback;
}

void Sandbox::stop() const
{
    glfwSetWindowShouldClose(_window, GL_TRUE);
}

void InternalWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    if (auto itr = sWindowSizeCallbackMap.find(window); itr != sWindowSizeCallbackMap.end())
    {
        itr->second(width, height);
    }
};

void InternalKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (auto itr = sKeyCallbackMap.find(window); itr != sKeyCallbackMap.end())
    {
        itr->second(key, scancode, action, mods);
    }
}

void InternalMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (auto itr = sMouseButtonCallbackMap.find(window); itr != sMouseButtonCallbackMap.end())
    {
        itr->second(button, action, mods);
    }
}

}
