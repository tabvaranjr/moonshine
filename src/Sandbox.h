#ifndef MOONSHINE_SANDBOX_H
#define MOONSHINE_SANDBOX_H

class GLFWwindow;

namespace Moonshine
{

class Sandbox
{
public:
    Sandbox();
    ~Sandbox();

private:
    GLFWwindow* window;
};

}

#endif //MOONSHINE_SANDBOX_H
