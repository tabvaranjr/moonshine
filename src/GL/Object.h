#ifndef MOONSHINE_GL_OBJECT_H
#define MOONSHINE_GL_OBJECT_H

namespace Moonshine::GL
{

class Object
{
public:
    constexpr auto GetId() const
    {
        return _id;
    }

protected:
    unsigned int _id;
};

}

#endif //MOONSHINE_GL_OBJECT_H
