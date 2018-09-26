#include "File.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <fmt/format.h>

namespace Moonshine::File
{

std::string readTextFile(const std::string& filename)
{
    std::ifstream ifs(filename.c_str());
    if (ifs)
    {
        std::stringstream sstr;
        sstr << ifs.rdbuf();
        ifs.close();
        return sstr.str();
    }
    else
    {
        throw std::runtime_error(fmt::format("Failed to open {0} for reading.", filename));
    }
}

}
