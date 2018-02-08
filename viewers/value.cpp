#include "value.h"

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
void NullableTypedViewerValue<T>::print(std::ostream& output) const
{
    output << this->_value;
}

void NullableTypedViewerValue<StringType>::print(std::ostream& output) const
{
    output << this->_value;
}

template<typename T>
ViewerByteBuffer TypedViewerValue<T>::get()
{
    uint64_t size = sizeof(_value);
    char* _val = reinterpret_cast<char*>(&_value);

    ViewerByteBuffer buffer(size, _val);

    return buffer;
}

ViewerByteBuffer TypedViewerValue<StringType>::get()
{
    uint64_t size = _value._size;
    char* _val = _value._buffer;

    ViewerByteBuffer buffer(size, _val);

    return buffer;
}

template<typename T>
ViewerByteBuffer NullableTypedViewerValue<T>::get() {
    ViewerByteBuffer buffer(0, nullptr);

    return buffer;
}

ViewerByteBuffer NullableTypedViewerValue<StringType>::get()
{
    ViewerByteBuffer buffer(0, nullptr);

    return buffer;
}

template<typename T>
void TypedViewerValue<T>::set(ViewerByteBuffer buff)
{
    this->_value = *reinterpret_cast<const type*>(buff._buffer);
}

void TypedViewerValue<StringType>::set(ViewerByteBuffer buff)
{
    _value = buff;
}

template<typename T>
void NullableTypedViewerValue<T>::set(ViewerByteBuffer buff) {}

void NullableTypedViewerValue<StringType>::set(ViewerByteBuffer buff) {}


template<typename T>
void TypedViewerValue<T>::cast(const std::string& value)
{
    this->_value = static_cast<type>(std::stoi(value));
}

template<>
void TypedViewerValue<Int64Type>::cast(const std::string& value)
{
    this->_value = static_cast<type>(std::stol(value));
}

template<>
void TypedViewerValue<FloatType>::cast(const std::string& value)
{
    this->_value = static_cast<type>(std::stof(value));
}

template<>
void TypedViewerValue<DoubleType>::cast(const std::string& value)
{
    this->_value = static_cast<type>(std::stod(value));
}

void TypedViewerValue<StringType>::cast(const std::string& value)
{
    this->_value = ViewerByteBuffer(value.size(), const_cast<char*>(value.data()));
}

template<typename T>
void NullableTypedViewerValue<T>::cast(const std::string& value) {}

void NullableTypedViewerValue<StringType>::cast(const std::string& value) {}
