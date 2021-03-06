#ifndef MOONSHINE_SANDBOX_H
#define MOONSHINE_SANDBOX_H

#include <functional>

struct GLFWwindow;

namespace Moonshine
{

class Sandbox
{
public:
    struct Parameters
    {
        unsigned int Width = 800;
        unsigned int Height = 600;
        bool IsDebugModeActive = true;
        bool IsFullScreen = false;
    };

    Sandbox();
    explicit Sandbox(Parameters p);
    ~Sandbox();

    void poolEvents();

    void swapBuffers() const;

    bool isStopping() const;

    void stop() const;

    void setWindowSizeCallback(std::function<void(int, int)> callback);

    void setKeyCallback(std::function<void(int, int, int, int)> callback);

    void setMouseButtonCallback(std::function<void(int, int, int)> callback);

private:
    GLFWwindow* _window;

    void startUpdate();
};

}

#endif //MOONSHINE_SANDBOX_H
