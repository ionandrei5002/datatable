#include "viewer_value.h"

std::ostream& operator <<(std::ostream& output, const ViewerValue& val)
{
    val.print(output);
    return output;
}

template<typename T>
void TypedViewerValue<T>::print(std::ostream& output) const
{
    output << this->_value;
}

void TypedViewerValue<StringType>::print(std::ostream& output) const
{
    output << this->_value;
}

template<typename T>
ViewerByteBuffer TypedViewerValue<T>::getValue()
{
    uint64_t size = sizeof(_value);
    char* _val = reinterpret_cast<char*>(&_value);

    ViewerByteBuffer buffer(size, _val);

    return buffer;
}

ViewerByteBuffer TypedViewerValue<StringType>::getValue()
{
    uint64_t size = _value._size;
    char* _val = _value._buffer;

    ViewerByteBuffer buffer(size, _val);

    return buffer;
}

template<typename T>
void TypedViewerValue<T>::setValue(ViewerByteBuffer buff)
{
    this->_value = *reinterpret_cast<const type*>(buff._buffer);
}

void TypedViewerValue<StringType>::setValue(ViewerByteBuffer buff)
{
    _value = buff;
}
