#include "Program.h"

#include "Shader.h"
#include <epoxy/gl.h>
#include <cassert>

namespace Moonshine::GL
{

Program::Program()
{
    _id = glCreateProgram();
}

Program::~Program()
{
    glDeleteProgram(_id);
}

void Program::attach(const Shader& shader)
{
    glAttachShader(_id, shader.id());
}

void Program::link()
{
    glLinkProgram(_id);
}

bool Program::status() const
{
    auto isLinked = 0;
    glGetProgramiv(_id, GL_LINK_STATUS, &isLinked);

    return isLinked == GL_TRUE;
}

std::string Program::infoLog() const
{
    auto logLength = 0;
    glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &logLength);

    std::string log;
    log.reserve(logLength);
    glGetProgramInfoLog(_id, logLength, nullptr, &log[0]);

    return log;
}

void Program::use() const
{
    assert(status());

    glUseProgram(_id);
}

}
