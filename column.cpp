#include "column.h"

std::unique_ptr<Column> Column::factory(Type::type type)
{
    std::unique_ptr<Column> value;
    switch (type) {
    case Type::INT8:
        value = std::make_unique<TypedColumn<Int8Type>>(TypedColumn<Int8Type>());
        break;
    case Type::INT16:
        value = std::make_unique<TypedColumn<Int16Type>>(TypedColumn<Int16Type>());
        break;
    case Type::INT32:
        value = std::make_unique<TypedColumn<Int32Type>>(TypedColumn<Int32Type>());
        break;
    case Type::INT64:
        value = std::make_unique<TypedColumn<Int64Type>>(TypedColumn<Int64Type>());
        break;
    case Type::FLOAT:
        value = std::make_unique<TypedColumn<FloatType>>(TypedColumn<FloatType>());
        break;
    case Type::DOUBLE:
        value = std::make_unique<TypedColumn<DoubleType>>(TypedColumn<DoubleType>());
        break;
    case Type::STRING:
        value = std::make_unique<TypedColumn<StringType>>(TypedColumn<StringType>());
        break;
    default:
        value = nullptr;
        break;
    }

    return value;
}

template<typename T>
void TypedColumn<T>::putValue(ViewerValue* value)
{
    TypedViewerValue<T> _value = *reinterpret_cast<TypedViewerValue<T>*>(value);

    ViewerByteBuffer buffer = _value.get();
    for(uint64_t i = 0; i < buffer._size; i++)
        _column.push_back(buffer._buffer[i]);

    nb_elements++;
}

template<typename T>
ViewerValue* TypedColumn<T>::getValue(size_t pos)
{
    typedef typename T::c_type type;
    uint64_t _size = sizeof(type);

    char* _value_position = const_cast<char*>(&_column[pos * _size]);
    ViewerByteBuffer buffer(_size, _value_position);

    _typedvalue.set(buffer);

    return &_typedvalue;
}

void TypedColumn<StringType>::putValue(ViewerValue* value)
{
    TypedViewerValue<StringType> _value = *reinterpret_cast<TypedViewerValue<StringType>*>(value);

    ViewerByteBuffer buffer = _value.get();
    uint8_t* size = reinterpret_cast<uint8_t*>(&buffer._size);

    uint64_t last_index = _column.size();

    for(uint64_t i = 0; i < sizeof(buffer._size); i++)
        _column.push_back(size[i]);
    for(uint64_t i = 0; i < buffer._size; i++)
        _column.push_back(buffer._buffer[i]);

    this->_position.push_back(last_index);

    nb_elements++;
}

ViewerValue* TypedColumn<StringType>::getValue(size_t pos)
{
    uint64_t buffer_position = this->_position[pos];

    uint64_t _size = *reinterpret_cast<uint64_t*>(&_column[buffer_position]);
    char* _value_position = const_cast<char*>(&_column[buffer_position + sizeof(_size)]);
    ViewerByteBuffer buffer(_size, _value_position);

    _typedvalue.set(buffer);

    return &_typedvalue;
}

void DictionaryTypedColumn<StringType>::putValue(ViewerValue* value)
{
    ViewerByteBuffer buffer = value->get();
    std::string str(buffer._buffer, buffer._size);

    auto pos = this->_column.find(str);
    if (pos == this->_column.end())
    {
        this->_column.insert(str);
        pos = this->_column.find(str);
    }

    this->_position.emplace_back(const_cast<std::string*>(&*pos));

    nb_elements++;
}

ViewerValue* DictionaryTypedColumn<StringType>::getValue(size_t pos)
{
    std::string* buffer_position = this->_position[pos];

    ViewerByteBuffer buffer(buffer_position->size(), const_cast<char*>(buffer_position->data()));

    _typedvalue.set(buffer);

    return &_typedvalue;
}
