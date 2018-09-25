#include "Buffer.h"

#include "../Helpers.h"
#include "glad/glad.h"

namespace Moonshine::GL
{

Buffer::Buffer()
{
    glCreateBuffers(1, &_id);
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &_id);
}

void Buffer::setData(const void* data, std::uintptr_t size, Buffer::Usage usage)
{
    glNamedBufferData(_id, size, data, ToUnderlyingType(usage));
}

}
