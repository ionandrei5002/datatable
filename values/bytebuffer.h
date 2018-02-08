#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

#include<memory>
#include<iostream>
#include<cstring>

class ByteBuffer {
public:
    uint64_t _size = 0;
    char* _buffer = nullptr;
public:
    ByteBuffer(uint64_t size, const char* buffer); // data copy init ctor
    ByteBuffer(const ByteBuffer& ot); // copy ctor
    ByteBuffer(ByteBuffer&& ot); // move ctor
    ByteBuffer& operator =(const ByteBuffer& ot); // copy operator
    ByteBuffer& operator =(ByteBuffer&& ot); // move operator
    ~ByteBuffer(); //dtor
    friend std::ostream &operator <<(std::ostream& output, const ByteBuffer& ot); // output operator
    friend std::istream &operator >>(std::istream& input, ByteBuffer& ot); // input operator
};

#endif // BYTEBUFFER_H
