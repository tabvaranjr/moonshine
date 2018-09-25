#include "Shader.h"

#include "../Helpers.h"
#include "glad/glad.h"

namespace Moonshine::GL
{

Shader::Shader(Type type)
{
    _id = glCreateShader(ToUnderlyingType(type));
}

Shader::~Shader()
{
    glDeleteShader(_id);
}

void Shader::setSource(const std::string& source) const
{
    auto sourcePtr = source.c_str();
    glShaderSource(_id, 1, &sourcePtr, nullptr);
}

void Shader::compile()
{
    glCompileShader(_id);
}

bool Shader::status() const
{
    auto isCompiled = 0;
    glGetShaderiv(_id, GL_COMPILE_STATUS, &isCompiled);

    return isCompiled == GL_TRUE;
}

std::string Shader::infoLog() const
{
    auto length = 0;
    glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &length);

    std::string log;
    log.resize(length);
    glGetShaderInfoLog(_id, length, nullptr, &log[0]);

    return log;
}

}
