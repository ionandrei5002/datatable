#ifndef COLUMNTEST_H
#define COLUMNTEST_H

#include "gtest.h"
#include "../column.h"

TEST(Columns, Int64TypeComparations)
{
    TypedColumn<Int64Type> column;
    std::vector<std::string> values {"10","4","3","11","7","6"};
    for(auto it  = values.begin(); it != values.end(); ++it)
    {
        TypedViewerValue<Int64Type> value;
        value.cast(&*it);
        column.putValue(value.get());
    }

    for(uint64_t i = 0; i < values.size(); i++)
    {
        ViewerByteBuffer value = column.getValue(i);
        TypedViewerValue<Int64Type> typed;
        typed.set(value);
        std::cout << typed << std::endl;
    }
}

#endif // COLUMNTEST_H
