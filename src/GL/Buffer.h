#ifndef MOONSHINE_GL_BUFFER_H
#define MOONSHINE_GL_BUFFER_H

#include "Object.h"
#include <vector>

namespace Moonshine::GL
{

class Buffer : public Object
{
    enum class Target : std::uint32_t
    {
        Array = 0x8892,
        AtomicCounter = 0x92C0,
        CopyRead = 0x8F36,
        CopyWrite = 0x8F37,
        DispatchIndirect = 0x90EE,
        DrawIndirect = 0x8F3F,
        ElementArray = 0x8893,
        PixelPack = 0x88EB,
        PixelUnpack = 0x88EC,
        Query = 0x9192,
        ShaderStorage = 0x90D2,
        Texture = 0x8C2A,
        TransformFeedback = 0x8C8E,
        Uniform = 0x8A11
    };

    enum class Access : std::uint32_t
    {
        ReadOnly = 0x88B8,
        WriteOnly = 0x88B9,
        ReadWrite = 0x88BA
    };

    enum class Usage : std::uint32_t
    {
        GL_STREAM_DRAW = 0x88E0,
        GL_STREAM_READ = 0x88E1,
        GL_STREAM_COPY = 0x88E2,
        GL_STATIC_DRAW = 0x88E4,
        GL_STATIC_READ = 0x88E5,
        GL_STATIC_COPY = 0x88E6,
        GL_DYNAMIC_DRAW = 0x88E8,
        GL_DYNAMIC_READ = 0x88E9,
        GL_DYNAMIC_COPY = 0x88EA,
    };

    Buffer();

    ~Buffer();

    void setData(void* data, std::uintptr_t size, Usage usage);

    template<typename T>
    constexpr void setData(const std::vector<T>& data, Usage usage)
    {
        setData(data.data(), data.size() * sizeof(T), usage);
    }

    void* map(Target target, Access access);
};

}

#endif //MOONSHINE_BUFFER_H
