#ifndef MOONSHINE_GL_SHADER_H
#define MOONSHINE_GL_SHADER_H

#include "Object.h"
#include <string>

namespace Moonshine::GL
{

class Shader : public Object
{
    enum class Type : std::uint32_t
    {
        Vertex = 0x8B31,
        TessControl = 0x8E88,
        TessEvaluation = 0x8E87,
        Geometry = 0x8DD9,
        Fragment = 0x8B30,
        Compute = 0x91B9
    };

    Shader(Type type);

    ~Shader();

    void setSource(const std::string& source) const;

    void compile();

    bool status() const;

    std::string infoLog() const;
};

}

#endif //MOONSHINE_SHADER_H
