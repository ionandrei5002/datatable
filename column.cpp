#include "column.h"

template<typename T>
void TypedColumn<T>::putValue(ViewerByteBuffer value)
{
    for(uint64_t i = 0; i < value._size; i++)
        _column.push_back(value._buffer[i]);

    nb_elements++;
}

template<typename T>
ViewerByteBuffer TypedColumn<T>::getValue(size_t pos)
{
    typedef typename T::c_type type;
    uint64_t _size = sizeof(type);

    char* _value_position = const_cast<char*>(&_column[pos * _size]);
    ViewerByteBuffer buffer(_size, _value_position);

    return buffer;
}

void TypedColumn<StringType>::putValue(ViewerByteBuffer value)
{
    uint8_t* size = reinterpret_cast<uint8_t*>(&value._size);

    uint64_t last_index = _column.size();

    for(uint64_t i = 0; i < sizeof(value._size); i++)
        _column.push_back(size[i]);
    for(uint64_t i = 0; i < value._size; i++)
        _column.push_back(value._buffer[i]);

    this->_position.push_back(last_index);

    nb_elements++;
}

ViewerByteBuffer TypedColumn<StringType>::getValue(size_t pos)
{
    uint64_t buffer_position = this->_position[pos];

    uint64_t _size = *reinterpret_cast<uint64_t*>(&_column[buffer_position]);
    char* _value_position = const_cast<char*>(&_column[buffer_position + sizeof(_size)]);
    ViewerByteBuffer buffer(_size, _value_position);

    return buffer;
}

void DictionaryTypedColumn<StringType>::putValue(ViewerByteBuffer value)
{
    std::string str(value._buffer, value._size);

    auto pos = this->_column.find(str);
    if (pos == this->_column.end())
    {
        this->_column.insert(str);
        pos = this->_column.find(str);
    }

    this->_position.emplace_back(const_cast<std::string*>(&*pos));

    nb_elements++;
}

ViewerByteBuffer DictionaryTypedColumn<StringType>::getValue(size_t pos)
{
    std::string* buffer_position = this->_position[pos];

    ViewerByteBuffer buffer(buffer_position->size(), const_cast<char*>(buffer_position->data()));

    return buffer;
}
