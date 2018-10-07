#include "Sandbox.h"

#include "TestObject.h"

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
        console->critical(u8"(┛◉Д◉)┛彡┻━┻: {0}\n", e.what());

        return 1;
    }

    return 0;
}
