#ifndef VIEWER_BYTEBUFFER_H
#define VIEWER_BYTEBUFFER_H

#include<memory>
#include<iostream>
#include<cstring>

class ByteBuffer {
public:
    uint64_t _size = 0;
    char* _buffer = nullptr;
public:
    ByteBuffer(); // default ctor
    ByteBuffer(uint64_t size); // zero init ctor
    ByteBuffer(uint64_t size, char* buffer); // data copy init ctor
    ByteBuffer(const ByteBuffer& ot); // copy ctor
    ByteBuffer(ByteBuffer&& ot); // move ctor
    ByteBuffer& operator =(const ByteBuffer& ot); // copy operator
    ByteBuffer& operator =(ByteBuffer&& ot); // move operator
    ~ByteBuffer(); //dtor
    friend std::ostream &operator <<(std::ostream& output, const ByteBuffer& ot); // output operator
    friend std::istream &operator >>(std::istream& input, ByteBuffer& ot); // input operator
};

class ViewerByteBuffer
{
public:
    uint64_t _size = 0;
    char* _buffer = nullptr;
public:
    ViewerByteBuffer(); // default ctor
    ViewerByteBuffer(uint64_t size); // zero init ctor
    ViewerByteBuffer(uint64_t size, char* buffer); // data copy init ctor
    ViewerByteBuffer(const ViewerByteBuffer& ot); // copy ctor
    ViewerByteBuffer(ViewerByteBuffer&& ot); // move ctor
    ViewerByteBuffer& operator =(const ViewerByteBuffer& ot); // copy operator
    ViewerByteBuffer& operator =(ViewerByteBuffer&& ot); // move operator
    ~ViewerByteBuffer(); //dtor
    friend std::ostream &operator <<(std::ostream& output, const ViewerByteBuffer& ot); // output operator
    friend std::istream &operator >>(std::istream& input, ViewerByteBuffer& ot); // input operator
};

#endif // VIEWER_BYTEBUFFER_H
