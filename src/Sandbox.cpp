#include "Sandbox.h"

#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <stdexcept>
#include <map>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
    auto console = spdlog::stdout_color_mt("console");

    auto glfwErrorCallback = [](auto error, auto description)
    {
        spdlog::get("console")->error("Error {0:#x}: {1}", error, description);
    };
    glfwSetErrorCallback(glfwErrorCallback);

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
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
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

        if (!gladLoadGL())
        {
            throw std::runtime_error("Could not load GL loader.");
        }

        spdlog::get("console")->info("Vendor: {0}", glGetString(GL_VENDOR));
        spdlog::get("console")->info("Renderer: {0}", glGetString(GL_RENDERER));
        spdlog::get("console")->info("Version: {0}", glGetString(GL_VERSION));

        if (!GLAD_GL_VERSION_4_5)
        {
            throw std::runtime_error("OpenGL 4.5 or later is required to use the sandbox.");
        }

        glfwSetWindowSizeCallback(_window, InternalWindowSizeCallback);
        glfwSetMouseButtonCallback(_window, InternalMouseButtonCallback);
        glfwSetKeyCallback(_window, InternalKeyCallback);

        if (p.IsDebugModeActive)
        {
            auto glDebugCallback = [](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                      const GLchar* message, const GLvoid* userParam)
            {
                switch (severity)
                {
                    case GL_DEBUG_SEVERITY_HIGH:
                        spdlog::get("console")->error("Error {0:#x}: {1}", id, message);
                        break;

                    case GL_DEBUG_SEVERITY_MEDIUM:
                        spdlog::get("console")->warn("Error {0:#x}: {1}", id, message);
                        break;

                    case GL_DEBUG_SEVERITY_LOW:
                        spdlog::get("console")->info("Error {0:#x}: {1}", id, message);
                        break;

                    case GL_DEBUG_SEVERITY_NOTIFICATION:
                    default:
                        spdlog::get("console")->debug("Error {0:#x}: {1}", id, message);
                        break;
                }
            };

            glDebugMessageCallback(glDebugCallback, nullptr);
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }

        // Setup Dear ImGui binding
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        ImGui_ImplGlfw_InitForOpenGL(_window, true);
        ImGui_ImplOpenGL3_Init("#version 150");

        // Setup style
        ImGui::StyleColorsDark();
    }
    catch (...)
    {
        glfwTerminate();
        throw;
    }
}

Sandbox::~Sandbox()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(_window);
    glfwTerminate();
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

void Sandbox::swapBuffers() const
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(_window);
}

void Sandbox::poolEvents()
{
    glfwPollEvents();
    startUpdate();
}

bool Sandbox::isStopping() const
{
    return glfwWindowShouldClose(_window);
}

void Sandbox::startUpdate()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
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
