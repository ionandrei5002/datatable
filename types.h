#ifndef TYPES
#define TYPES

#include <memory>
#include "viewer_bytebuffer.h"

struct Type
{
    enum type
    {
        INT8 = 1,
        INT16 = 2,
        INT32 = 3,
        INT64 = 4,
        FLOAT = 5,
        DOUBLE = 6,
        STRING = 7
    };
};

struct Encoding {
    enum type {
        PLAIN = 1,
        DICTIONARY = 2
    };
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
    typedef ViewerByteBuffer value_type;
    static constexpr char* name = const_cast<char*>("STRING");
    static constexpr int value_byte_size = sizeof(ViewerByteBuffer);
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
