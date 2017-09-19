#ifndef MOONSHINE_GL_VERTEXARRAY_H
#define MOONSHINE_GL_VERTEXARRAY_H

#include "Object.h"

namespace Moonshine::GL
{

class Buffer;

class VertexArray : public Object
{
public:
    enum class Type : std::uint32_t
    {
        Byte = 0x1400,
        UnsignedByte = 0x1401,
        Short = 0x1402,
        UnsignedShort = 0x1403,
        Int = 0x1404,
        UnsignedInt = 0x1405,
        Float = 0x1406,
        Double = 0x140A,
        HalfFloat = 0x140B,
        Fixed = 0x140C
    };

    VertexArray();
    ~VertexArray();

    void bind();

    void bindBuffer(std::uint32_t index, const Buffer& buffer, std::intptr_t offset = 0, std::intptr_t stride = 0);

    void setAttribFormat(std::uint32_t index, std::int32_t size, Type type, bool normalized = false, std::uint32_t relativeoffset = 0);
    void setAttribIFormat(std::uint32_t index, std::int32_t size, Type type, bool normalized = false, std::uint32_t relativeoffset = 0);

    void enableAttrib(std::uint32_t index);
    void disableAttrib(std::uint32_t index);
};

}

#endif //MOONSHINE_VERTEXARRAY_H
