#ifndef VIEWER_VALUE_H
#define VIEWER_VALUE_H

#include <memory>
#include <experimental/string_view>

#include "types.h"
#include "viewer_bytebuffer.h"

class ViewerValue
{
public:
    virtual ~ViewerValue() {}
    virtual void setValue(ViewerByteBuffer buff) = 0;
    virtual ViewerByteBuffer getValue() = 0;
    friend std::ostream& operator <<(std::ostream& output, const ViewerValue& val);
    virtual void print(std::ostream& output) const = 0;
    virtual Type::type getType() = 0;
};

template<typename T>
class TypedViewerValue: public ViewerValue {
private:
    typename T::c_type _value;
    typedef typename T::c_type type;
public:
    TypedViewerValue():_value(type(0)){}
    void setValue(ViewerByteBuffer buff) override;
    ViewerByteBuffer getValue() override;
    void print(std::ostream& output) const override;
    bool operator <(const TypedViewerValue<T>& val)
    {
        return _value < val._value;
    }
    friend bool operator <(const TypedViewerValue<T>& lv, const TypedViewerValue<T>& rv)
    {
        return lv._value < rv._value;
    }
    bool operator ==(const TypedViewerValue<T>& val)
    {
        return !(_value < val._value) && !(val._value < _value);
    }
    bool operator !=(const TypedViewerValue<T>& val)
    {
        return !this->operator ==(val);
    }
    Type::type getType() override
    {
        return T::type_num;
    }
};

template<typename T>
class NullableTypedViewerValue: public ViewerValue {
private:
    typename T::c_type _value;
    typedef typename T::c_type type;
public:
    NullableTypedViewerValue():_value(type(0)){}
    void setValue(ViewerByteBuffer buff) override;
    ViewerByteBuffer getValue() override;
    void print(std::ostream& output) const override;
    bool operator <(const NullableTypedViewerValue<T>& val)
    {
        return _value < val._value;
    }
    friend bool operator <(const NullableTypedViewerValue<T>& lv, const NullableTypedViewerValue<T>& rv)
    {
        return lv._value < rv._value;
    }
    bool operator ==(const NullableTypedViewerValue<T>& val)
    {
        return !(_value < val._value) && !(val._value < _value);
    }
    bool operator !=(const NullableTypedViewerValue<T>& val)
    {
        return !this->operator ==(val);
    }
    Type::type getType() override
    {
        return T::type_num;
    }
};

template<>
class TypedViewerValue<StringType>: public ViewerValue {
private:
    StringType::c_type _value;
    typedef typename StringType::c_type type;
public:
    TypedViewerValue():_value(type()){}
    void setValue(ViewerByteBuffer buff) override;
    ViewerByteBuffer getValue() override;
    void print(std::ostream& output) const override;
    bool operator <(const TypedViewerValue<StringType>& val)
    {
        return std::experimental::string_view(reinterpret_cast<char*>(this->_value._buffer), this->_value._size)
                < std::experimental::string_view(reinterpret_cast<char*>(val._value._buffer), val._value._size);
    }
    friend bool operator <(const TypedViewerValue<StringType>& lv, const TypedViewerValue<StringType>& rv)
    {
        return std::experimental::string_view(reinterpret_cast<char*>(lv._value._buffer), lv._value._size)
                < std::experimental::string_view(reinterpret_cast<char*>(rv._value._buffer), rv._value._size);
    }
    bool operator ==(const TypedViewerValue<StringType>& val)
    {
        return std::experimental::string_view(reinterpret_cast<char*>(this->_value._buffer), this->_value._size)
                == std::experimental::string_view(reinterpret_cast<char*>(val._value._buffer), val._value._size);
    }
    bool operator !=(const TypedViewerValue<StringType>& val)
    {
        return !this->operator ==(val);
    }
    Type::type getType() override
    {
        return StringType::type_num;
    }
};

template class TypedViewerValue<Int8Type>;
template class TypedViewerValue<Int16Type>;
template class TypedViewerValue<Int32Type>;
template class TypedViewerValue<Int64Type>;
template class TypedViewerValue<FloatType>;
template class TypedViewerValue<DoubleType>;
template class TypedViewerValue<StringType>;

#endif // VIEWER_VALUE_H