#ifndef VALUE_H
#define VALUE_H

#include "../types.h"
#include "bytebuffer.h"

class Value {
public:
    virtual ~Value() {}
    virtual void cast(const std::string& value) = 0;
    virtual ByteBuffer get() = 0;
    friend std::ostream& operator <<(std::ostream& output, const Value& val);
    virtual void print(std::ostream& output) const = 0;
    virtual Type::type getType() = 0;
    virtual bool isNull() = 0;
};

template<typename T>
class TypedValue: public Value {
private:
    typename T::c_type _value;
    typedef typename T::c_type type;
public:
    TypedValue();
    void cast(const std::string& value) override;
    ByteBuffer get() override;
    void print(std::ostream& output) const override;
    Type::type getType() override
    {
        return T::type_num;
    }
    bool isNull() override
    {
        return false;
    }
};

template<typename T>
class NullableTypedValue: public Value {
private:
    bool _isNull = false;
    typename T::c_type _value;
    typedef typename T::c_type type;
public:
    NullableTypedValue();
    void cast(const std::string& value) override;
    ByteBuffer get() override;
    void print(std::ostream& output) const override;
    Type::type getType() override
    {
        return T::type_num;
    }
    bool isNull() override
    {
        return this->_isNull;
    }
};

template class TypedValue<Int8Type>;
template class TypedValue<Int16Type>;
template class TypedValue<Int32Type>;
template class TypedValue<Int64Type>;
template class TypedValue<FloatType>;
template class TypedValue<DoubleType>;
template class TypedValue<StringType>;

template class NullableTypedValue<Int8Type>;
template class NullableTypedValue<Int16Type>;
template class NullableTypedValue<Int32Type>;
template class NullableTypedValue<Int64Type>;
template class NullableTypedValue<FloatType>;
template class NullableTypedValue<DoubleType>;
template class NullableTypedValue<StringType>;

#endif // VALUE_H
