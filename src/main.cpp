#include <stdexcept>
#include <fmt/format.h>

#include "Sandbox.h"

int main(int argc, char* argv[])
{
    try
    {
        Moonshine::Sandbox box;
    }
    catch (std::exception& e)
    {
        fmt::print("(┛◉Д◉)┛彡┻━┻: {0}\n", e.what());

        return 1;
    }

    return 0;
}
