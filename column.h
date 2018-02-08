#ifndef COLUMN_H
#define COLUMN_H

#include <vector>
#include <set>

#include "types.h"
#include "viewers/value.h"

class Column
{
protected:
    std::vector<char> _column;    
    uint64_t nb_elements = 0;
public:
    Column():_column(std::vector<char>()),nb_elements(0){}
    virtual ~Column(){}
    static std::unique_ptr<Column> factory(Type::type type);
    virtual void putValue(ViewerValue* value) = 0;
    virtual ViewerValue* getValue(size_t pos) = 0;
    virtual Type::type getType() = 0;
};

template<typename T>
class TypedColumn: public Column
{
private:
    TypedViewerValue<T> _typedvalue;
    Type::type _type = T::type_num;
public:
    TypedColumn():_typedvalue(TypedViewerValue<T>())
    {
        Column::Column();
    }
    Type::type getType() override { return _type; }
    void putValue(ViewerValue* value) override;
    ViewerValue* getValue(size_t pos) override;
};

template<>
class TypedColumn<StringType>: public Column
{
private:
    std::vector<uint64_t> _position;
    TypedViewerValue<StringType> _typedvalue;
    Type::type _type = StringType::type_num;
public:
    TypedColumn():Column::Column(),_position(std::vector<uint64_t>()), _typedvalue(TypedViewerValue<StringType>()) {}
    Type::type getType() override { return _type; }
    void putValue(ViewerValue* value) override;
    ViewerValue* getValue(size_t pos) override;
};

template<typename T>
class NullableTypedColumn: public Column
{
private:
    std::vector<uint8_t> _nullable;
    TypedViewerValue<T> _typedvalue;
    Type::type _type = T::type_num;
public:
    NullableTypedColumn():_nullable(std::vector<uint8_t>()),_typedvalue(TypedViewerValue<T>())
    {
        Column::Column();
    }
    Type::type getType() override { return _type; }
    void putValue(ViewerValue* value) override;
    ViewerValue* getValue(size_t pos) override;
};

template<>
class NullableTypedColumn<StringType>: public Column
{
private:
    std::vector<uint64_t> _position;
    std::vector<uint8_t> _nullable;
    TypedViewerValue<StringType> _typedvalue;
    Type::type _type = StringType::type_num;
public:
    NullableTypedColumn():Column::Column(),_position(std::vector<uint64_t>()),_nullable(std::vector<uint8_t>()),_typedvalue(TypedViewerValue<StringType>()) {}
    Type::type getType() override { return _type; }
    void putValue(ViewerValue* value) override;
    ViewerValue* getValue(size_t pos) override;
};


template class TypedColumn<Int8Type>;
template class TypedColumn<Int16Type>;
template class TypedColumn<Int32Type>;
template class TypedColumn<Int64Type>;
template class TypedColumn<FloatType>;
template class TypedColumn<DoubleType>;
template class TypedColumn<StringType>;


#endif // COLUMN_H
