#include "Sandbox.h"

#include "TestObject.h"
#include "Entity.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <stdexcept>
#include <memory>
#include <imgui.h>
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"


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

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();


            entity->render();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
