#ifndef TYPES
#define TYPES

#include <memory>
#include "values/bytebuffer.h"

struct Type
{
    enum type
    {
        INT8 = 0,
        INT16 = 1,
        INT32 = 2,
        INT64 = 3,
        FLOAT = 4,
        DOUBLE = 5,
        STRING = 6
    };
};

struct Encoding {
    enum type {
        PLAIN = 0,
        DICTIONARY = 1
    };
};

template<typename T>
struct enum_traits
{
};

template<>
struct enum_traits<Type>
{
    static constexpr uint32_t min_value = 0;
    static constexpr uint32_t max_value = 6;
    static constexpr uint32_t elements = 7;
};

template<>
struct enum_traits<Encoding>
{
    static constexpr uint32_t min_value = 0;
    static constexpr uint32_t max_value = 1;
    static constexpr uint32_t elements = 2;
};

template<int TYPE>
struct type_traits
{
};

template<>
struct type_traits<Type::INT8>
{
    typedef int8_t value_type;
    static constexpr char* name = const_cast<char*>("INT8");
    static constexpr int value_byte_size = 1;
};

template<>
struct type_traits<Type::INT16>
{
    typedef int16_t value_type;
    static constexpr char* name = const_cast<char*>("INT16");
    static constexpr int value_byte_size = 2;
};

template<>
struct type_traits<Type::INT32>
{
    typedef int32_t value_type;
    static constexpr char* name = const_cast<char*>("INT32");
    static constexpr int value_byte_size = 4;
};

template<>
struct type_traits<Type::INT64>
{
    typedef int64_t value_type;
    static constexpr char* name = const_cast<char*>("INT64");
    static constexpr int value_byte_size = 8;
};

template<>
struct type_traits<Type::FLOAT>
{
    typedef float value_type;
    static constexpr char* name = const_cast<char*>("FLOAT");
    static constexpr int value_byte_size = 4;
};

template<>
struct type_traits<Type::DOUBLE>
{
    typedef double value_type;
    static constexpr char* name = const_cast<char*>("DOUBLE");
    static constexpr int value_byte_size = 8;
};

template<>
struct type_traits<Type::STRING>
{
    typedef ByteBuffer value_type;
    static constexpr char* name = const_cast<char*>("STRING");
    static constexpr int value_byte_size = sizeof(ByteBuffer);
};

template<Type::type TYPE>
struct DataType
{
    static constexpr Type::type type_num = TYPE;
    static constexpr char* name = type_traits<TYPE>::name;
    typedef typename type_traits<TYPE>::value_type c_type;
};

typedef DataType<Type::INT8> Int8Type;
typedef DataType<Type::INT16> Int16Type;
typedef DataType<Type::INT32> Int32Type;
typedef DataType<Type::INT64> Int64Type;
typedef DataType<Type::FLOAT> FloatType;
typedef DataType<Type::DOUBLE> DoubleType;
typedef DataType<Type::STRING> StringType;

#endif // TYPES
