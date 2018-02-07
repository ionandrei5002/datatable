#include "viewer_bytebuffer.h"

ByteBuffer::ByteBuffer()
{
    _size = 0;
    _buffer = nullptr;
}

ByteBuffer::ByteBuffer(uint64_t size)
{
    _size = size;
}

ByteBuffer::ByteBuffer(uint64_t size, char *buffer)
{
    _size = size;
    _buffer = new char[size];
    memcpy(_buffer, buffer, size);
}

ByteBuffer::ByteBuffer(const ByteBuffer &ot)
{
    _size = ot._size;
    _buffer = new char[ot._size];
    memcpy(_buffer, ot._buffer, ot._size);
}

ByteBuffer::ByteBuffer(ByteBuffer &&ot)
{
    _size = ot._size;
    _buffer = ot._buffer;

    ot._size = 0;
    ot._buffer = nullptr;
}

ByteBuffer& ByteBuffer::operator =(const ByteBuffer& ot)
{
    _size = ot._size;
    _buffer = new char[ot._size];
    memcpy(_buffer, ot._buffer, ot._size);

    return *this;
}

ByteBuffer& ByteBuffer::operator =(ByteBuffer&& ot)
{
    _size = ot._size;
    _buffer = ot._buffer;

    ot._size = 0;
    ot._buffer = nullptr;

    return *this;
}

ByteBuffer::~ByteBuffer()
{
    if (_buffer != nullptr) {
        delete[] _buffer;
    }

    _buffer = nullptr;
    _size = 0;
}

std::ostream& operator <<(std::ostream& output, const ByteBuffer& ot)
{
    for(uint64_t i = 0; i < ot._size; i++)
    {
        output << ot._buffer[i];
    }

    return output;
}

std::istream& operator >>(std::istream& input, ByteBuffer& ot)
{
    return input;
}

/********************************************************************/

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
