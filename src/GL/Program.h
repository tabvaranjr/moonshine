#ifndef MOONSHINE_GL_PROGRAM_H
#define MOONSHINE_GL_PROGRAM_H

#include "Object.h"
#include <string>
#include <initializer_list>

namespace Moonshine::GL
{

class Shader;

class Program : public Object
{
public:
    Program();

    ~Program();

    void attach(const Shader& shader);
    void attach(std::initializer_list<const Shader> list);

    void link();

    bool status() const;

    std::string infoLog() const;

    void use() const;
};

}

#endif //MOONSHINE_GL_PROGRAM_H
