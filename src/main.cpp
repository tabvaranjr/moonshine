#include "Sandbox.h"

#include "TestObject.h"
#include "Entity.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <stdexcept>
#include <memory>

int main(int argc, char* argv[])
{
    auto console = spdlog::stdout_color_mt("console");
    spdlog::set_level(spdlog::level::info);

    try
    {
        auto box = std::make_shared<Moonshine::Sandbox>();
        auto entity = std::make_shared<Moonshine::TestObject>();

        while (true)
        {
            if (box->isStopping())
            {
                break;
            }

            box->poolEvents();

            entity->render();

            box->swapBuffers();
        }
    }
    catch (std::exception& e)
    {
        console->critical(u8"(┛◉Д◉)┛彡┻━┻: {0}\n", e.what());

        return 1;
    }

    return 0;
}
