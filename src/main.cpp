#include "Sandbox.h"

#include "TestObject.h"

#include "glad/glad.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <stdexcept>

int main(int argc, char* argv[])
{
    auto console = spdlog::stdout_color_mt("console");
    spdlog::set_level(spdlog::level::info);

    try
    {
        Moonshine::Sandbox box;

        auto windowSizeCallback = [](int width, int height)
        {
            spdlog::get("console")->info("Viewport changed to {0}x{1}", width, height);
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

        Moonshine::TestObject testobj;

        while (true)
        {
            if (box.isStopping())
            {
                break;
            }

            box.poolEvents();

            testobj.render();

            box.swapBuffers();
        }
    }
    catch (std::exception& e)
    {
        console->critical("(┛◉Д◉)┛彡┻━┻: {0}\n", e.what());

        return 1;
    }

    return 0;
}
