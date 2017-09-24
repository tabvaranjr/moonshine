#include "Sandbox.h"

#include <epoxy/gl.h>
#include <stdexcept>
#include <fmt/format.h>

int main(int argc, char* argv[])
{
    try
    {
        Moonshine::Sandbox box;
        box.printRendererInformation();

        auto windowSizeCallback = [](int width, int height)
        {
            fmt::print("{0}x{1}\n", width, height);
            glViewport(0, 0, width, height);
        };

        auto keyCallback = [&box](auto key, auto scancode, auto action, auto mods)
        {
            if (key == 256 && action == 1)
            {
                box.stop();
            }
        };

        box.setWindowSizeCallback(windowSizeCallback);
        box.setKeyCallback(keyCallback);
        box.run();
    }
    catch (std::exception& e)
    {
        fmt::print("(┛◉Д◉)┛彡┻━┻: {0}\n", e.what());

        return 1;
    }

    return 0;
}
