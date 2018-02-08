#include "bytebuffer.h"

ViewerByteBuffer::ViewerByteBuffer()
{
    _size = 0;
    _buffer = nullptr;
}

ViewerByteBuffer::ViewerByteBuffer(uint64_t size)
{
    _size = size;
}

ViewerByteBuffer::ViewerByteBuffer(uint64_t size, char *buffer)
{
    _size = size;
    _buffer = buffer;
}

ViewerByteBuffer::ViewerByteBuffer(const ViewerByteBuffer &ot)
{
    _size = ot._size;
    _buffer = ot._buffer;
}

ViewerByteBuffer::ViewerByteBuffer(ViewerByteBuffer &&ot)
{
    _size = ot._size;
    _buffer = ot._buffer;

    ot._size = 0;
    ot._buffer = nullptr;
}

ViewerByteBuffer& ViewerByteBuffer::operator =(const ViewerByteBuffer& ot)
{
    _size = ot._size;
    _buffer = ot._buffer;

    return *this;
}

ViewerByteBuffer& ViewerByteBuffer::operator =(ViewerByteBuffer&& ot)
{
    _size = ot._size;
    _buffer = ot._buffer;

    ot._size = 0;
    ot._buffer = nullptr;

    return *this;
}

ViewerByteBuffer::~ViewerByteBuffer()
{
    _buffer = nullptr;
    _size = 0;
}

std::ostream& operator <<(std::ostream& output, const ViewerByteBuffer& ot)
{
    for(uint64_t i = 0; i < ot._size; i++)
    {
        output << ot._buffer[i];
    }

    return output;
}

std::istream& operator >>(std::istream& input, ViewerByteBuffer& ot)
{
    return input;
}
