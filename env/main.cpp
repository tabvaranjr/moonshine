#include "Sandbox.h"

#include "TestObject.h"
#include "Entity.h"

#include <spdlog/spdlog.h>
#include <stdexcept>
#include <memory>
#include <fmt/format.h>

int main(int argc, char* argv[])
{
    spdlog::set_level(spdlog::level::info);

    try
    {
        auto box = std::make_shared<Moonshine::Sandbox>();
        auto entity = std::make_shared<Moonshine::TestObject>();

        while (!box->isStopping())
        {
            // Process input.
            box->poolEvents();

            // Update.
            entity->update();

            // Render.
            entity->render();

            box->swapBuffers();
        }
    }
    catch (std::exception& e)
    {
        fmt::format(u8"(┛◉Д◉)┛彡┻━┻: {0}\n", e.what());

        return 1;
    }

    return 0;
}
