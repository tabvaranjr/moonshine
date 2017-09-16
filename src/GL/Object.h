#ifndef MOONSHINE_GL_OBJECT_H
#define MOONSHINE_GL_OBJECT_H

#include <cstdint>

namespace Moonshine::GL
{

class Object
{
public:
    constexpr auto id() const
    {
        return _id;
    }

protected:
    std::uint32_t _id;
};

}

#endif //MOONSHINE_GL_OBJECT_H
