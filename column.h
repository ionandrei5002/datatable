#ifndef COLUMN_H
#define COLUMN_H

#include <vector>
#include <set>

#include "types.h"
#include "viewers/value.h"

#include "iterators/iterator.h"

class Column
{
protected:   
    uint64_t nb_elements = 0;
public:
    Column():nb_elements(0){}
    virtual ~Column(){}
    virtual void putValue(ViewerByteBuffer value) = 0;
    virtual ViewerByteBuffer getValue(size_t pos) = 0;
    virtual Type::type getType() = 0;
};

template<typename T>
class TypedColumn: public Column
{
private:
    std::vector<char> _column;
    TypedViewerValue<T> _typedvalue;
    Type::type _type = T::type_num;
public:
    using iterator = ColumnIterator<T>;
    TypedColumn()
        :Column::Column(),
          _column(std::vector<char>()),
          _typedvalue(TypedViewerValue<T>()) {}
    Type::type getType() override { return _type; }
    void putValue(ViewerByteBuffer value) override;
    ViewerByteBuffer getValue(size_t pos) override;
    iterator begin() const
    {
        return ColumnIterator<T>(0, const_cast<TypedColumn<T>*>(this));
    }

    iterator end() const
    {
        return ColumnIterator<T>(nb_elements, const_cast<TypedColumn<T>*>(this));
    }
};

template<>
class TypedColumn<StringType>: public Column
{
private:
    std::vector<char> _column;
    std::vector<uint64_t> _position;
    TypedViewerValue<StringType> _typedvalue;
    Type::type _type = StringType::type_num;
public:
    using iterator = ColumnIterator<StringType>;
    TypedColumn()
        :Column::Column(),
          _column(std::vector<char>()),
          _position(std::vector<uint64_t>()),
          _typedvalue(TypedViewerValue<StringType>()) {}
    Type::type getType() override { return _type; }
    void putValue(ViewerByteBuffer value) override;
    ViewerByteBuffer getValue(size_t pos) override;
    iterator begin() const
    {
        return ColumnIterator<StringType>(0, const_cast<TypedColumn<StringType>*>(this));
    }

    iterator end() const
    {
        return ColumnIterator<StringType>(nb_elements, const_cast<TypedColumn<StringType>*>(this));
    }
};

template<typename T>
class NullableTypedColumn: public Column
{
private:
    std::vector<char> _column;
    std::vector<uint8_t> _nullable;
    TypedViewerValue<T> _typedvalue;
    Type::type _type = T::type_num;
public:
    NullableTypedColumn()
        :Column::Column(),
          _column(std::vector<char>()),
          _nullable(std::vector<uint8_t>()),
          _typedvalue(TypedViewerValue<T>()) {}
    Type::type getType() override { return _type; }
    void putValue(ViewerByteBuffer value) override;
    ViewerByteBuffer getValue(size_t pos) override;
};

template<>
class NullableTypedColumn<StringType>: public Column
{
private:
    std::vector<char> _column;
    std::vector<uint64_t> _position;
    std::vector<uint8_t> _nullable;
    TypedViewerValue<StringType> _typedvalue;
    Type::type _type = StringType::type_num;
public:
    NullableTypedColumn()
        :Column::Column(),
          _position(std::vector<uint64_t>()),
          _nullable(std::vector<uint8_t>()),
          _typedvalue(TypedViewerValue<StringType>()) {}
    Type::type getType() override { return _type; }
    void putValue(ViewerByteBuffer value) override;
    ViewerByteBuffer getValue(size_t pos) override;
};

template<typename T>
class DictionaryTypedColumn: public Column
{
private:
    std::set<std::string> _column;
    std::vector<std::string*> _position;
    TypedViewerValue<T> _typedvalue;
    Type::type _type = T::type_num;
public:
    DictionaryTypedColumn()
        :Column::Column(),
          _column(std::set<std::string>()),
          _position(std::vector<std::string*>()),
          _typedvalue(TypedViewerValue<T>()) {}
    Type::type getType() override { return _type; }
    void putValue(ViewerByteBuffer value) override {}
    ViewerByteBuffer getValue(size_t pos) override {return nullptr;}
};

template<>
class DictionaryTypedColumn<StringType>: public Column
{
private:
    std::set<std::string> _column;
    std::vector<std::string*> _position;
    TypedViewerValue<StringType> _typedvalue;
    Type::type _type = StringType::type_num;
public:
    DictionaryTypedColumn()
        :Column::Column(),
          _column(std::set<std::string>()),
          _position(std::vector<std::string*>()),
          _typedvalue(TypedViewerValue<StringType>()) {}
    Type::type getType() override { return _type; }
    void putValue(ViewerByteBuffer value) override;
    ViewerByteBuffer getValue(size_t pos) override;
};

template class TypedColumn<Int8Type>;
template class TypedColumn<Int16Type>;
template class TypedColumn<Int32Type>;
template class TypedColumn<Int64Type>;
template class TypedColumn<FloatType>;
template class TypedColumn<DoubleType>;
template class TypedColumn<StringType>;


#endif // COLUMN_H
