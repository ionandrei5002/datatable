#include "value.h"

template<typename T>
TypedValue<T>::TypedValue():_value(0) {}

template<>
TypedValue<StringType>::TypedValue():_value(ByteBuffer(0, nullptr)) {}

std::ostream& operator <<(std::ostream& output, const Value& val)
{
    val.print(output);
    return output;
}

template<typename T>
NullableTypedValue<T>::NullableTypedValue():_value(0) {}

template<>
NullableTypedValue<StringType>::NullableTypedValue():_value(ByteBuffer(0, nullptr)) {}

template<typename T>
void TypedValue<T>::print(std::ostream& output) const
{
    output << this->_value;
}

template<>
void TypedValue<StringType>::print(std::ostream& output) const
{
    output << this->_value;
}

template<typename T>
ByteBuffer TypedValue<T>::get()
{
    uint64_t size = sizeof(_value);
    char* _val = reinterpret_cast<char*>(&_value);

    ByteBuffer buffer(size, _val);

    return std::move(buffer);
}

template<>
ByteBuffer TypedValue<StringType>::get()
{
    uint64_t size = _value._size;
    char* _val = _value._buffer;

    ByteBuffer buffer(size, _val);

    return std::move(buffer);
}

template<typename T>
void TypedValue<T>::cast(const std::string& value)
{
    this->_value = static_cast<type>(std::stoi(value));
}

template<>
void TypedValue<Int64Type>::cast(const std::string& value)
{
    this->_value = static_cast<type>(std::stol(value));
}

template<>
void TypedValue<FloatType>::cast(const std::string& value)
{
    this->_value = static_cast<type>(std::stof(value));
}

template<>
void TypedValue<DoubleType>::cast(const std::string& value)
{
    this->_value = static_cast<type>(std::stod(value));
}

template<>
void TypedValue<StringType>::cast(const std::string& value)
{
    this->_value = ByteBuffer(value.size(), value.data());
}



template<typename T>
void NullableTypedValue<T>::print(std::ostream& output) const
{
    if (this->_isNull == false)
        output << this->_value;
    else
        output << "NULL";
}

template<>
void NullableTypedValue<StringType>::print(std::ostream& output) const
{
    if (this->_isNull == false)
        output << this->_value;
    else
        output << "NULL";
}

template<typename T>
ByteBuffer NullableTypedValue<T>::get()
{
    uint64_t size = sizeof(_value);
    char* _val = reinterpret_cast<char*>(&_value);

    ByteBuffer buffer(size, _val);

    return std::move(buffer);
}

template<>
ByteBuffer NullableTypedValue<StringType>::get()
{
    uint64_t size = _value._size;
    char* _val = _value._buffer;

    ByteBuffer buffer(size, _val);

    return std::move(buffer);
}

template<typename T>
void NullableTypedValue<T>::cast(const std::string& value)
{
    if (value == "NULL")
    {
        this->_isNull = true;
        this->_value = 0;
    } else {
        this->_value = static_cast<type>(std::stoi(value));
    }
}

template<>
void NullableTypedValue<Int64Type>::cast(const std::string& value)
{
    if (value == "NULL")
    {
        this->_isNull = true;
        this->_value = 0;
    } else {
        this->_value = static_cast<type>(std::stol(value));
    }
}

template<>
void NullableTypedValue<FloatType>::cast(const std::string& value)
{
    if (value == "NULL")
    {
        this->_isNull = true;
        this->_value = 0;
    } else {
        this->_value = static_cast<type>(std::stof(value));
    }
}

template<>
void NullableTypedValue<DoubleType>::cast(const std::string& value)
{
    if (value == "NULL")
    {
        this->_isNull = true;
        this->_value = 0;
    } else {
        this->_value = static_cast<type>(std::stod(value));
    }
}

template<>
void NullableTypedValue<StringType>::cast(const std::string& value)
{
    if (value == "NULL")
    {
        this->_isNull = true;
        this->_value = ByteBuffer(0, nullptr);
    } else {
        this->_value = ByteBuffer(value.size(), value.data());
    }
}
