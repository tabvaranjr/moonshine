#ifndef MOONSHINE_SANDBOX_H
#define MOONSHINE_SANDBOX_H

class GLFWwindow;

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

private:
    GLFWwindow* window;
};

}

#endif //MOONSHINE_SANDBOX_H
