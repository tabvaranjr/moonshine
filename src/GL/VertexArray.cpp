#include "VertexArray.h"

#include "../Helpers.h"
#include "Buffer.h"
#include <epoxy/gl.h>

namespace Moonshine::GL
{

VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &_id);
}

void VertexArray::bind()
{
    glBindVertexArray(_id);
}

void VertexArray::bindBuffer(std::uint32_t index, const Buffer& buffer, std::intptr_t offset, std::intptr_t stride)
{
    glVertexArrayVertexBuffer(_id, index, buffer.id(), offset, stride);
}

void VertexArray::setAttribFormat(std::uint32_t index, std::int32_t size, Type type, bool normalized,
                                  std::uint32_t relativeoffset)
{
    if (type == Type::Double)
    {
        glVertexArrayAttribLFormat(_id, index, size, ToUnderlyingType(type), relativeoffset);
    }
    else
    {
        glVertexArrayAttribFormat(_id, index, size, ToUnderlyingType(type), normalized, relativeoffset);
    }
}

void VertexArray::setAttribIFormat(std::uint32_t index, std::int32_t size, Type type, bool normalized,
                                   std::uint32_t relativeoffset)
{
    glVertexArrayAttribIFormat(_id, index, size, ToUnderlyingType(type), relativeoffset);
}

void VertexArray::enableAttrib(std::uint32_t index)
{
    glEnableVertexArrayAttrib(_id, index);
}

void VertexArray::disableAttrib(std::uint32_t index)
{
    glDisableVertexArrayAttrib(_id, index);
}

}
