#ifndef COMPARATORTEST_H
#define COMPARATORTEST_H

#include "gtest.h"
#include "../comparators/comparator.h"
#include "../column.h"
#include "../iterators/iterator.h"

#include <vector>
#include <algorithm>

TEST(Comparators, Sorter)
{
    std::shared_ptr<TypedColumn<StringType>> column = std::make_shared<TypedColumn<StringType>>(TypedColumn<StringType>());
    TypedViewerValue<StringType> value;
    std::vector<int64_t> order;
    std::vector<std::string> values {"10","4","3","11","7","6"};
    uint64_t pos = 0;
    for(auto it = values.begin(); it != values.end(); ++it)
    {
        value.cast(&(*it));
        column->putValue(&value);
        order.push_back(pos);
        pos++;
    }

    TypedComparator<StringType> comparator(column.get());
    std::sort(order.begin(), order.end(), comparator._sort);

    for(auto it = order.begin(); it != order.end(); ++it)
    {
        std::cout << *column->getValue(*it) << std::endl;
    }

}

TEST(Comparators, ByteBufferSorter)
{
    std::shared_ptr<TypedColumn<StringType>> column = std::make_shared<TypedColumn<StringType>>(TypedColumn<StringType>());
    TypedViewerValue<StringType> value;

    std::vector<std::string> values {"10","4","3","11","7","6"};
    for(auto it = values.begin(); it != values.end(); ++it)
    {
        value.cast(&(*it));
        column->putValue(&value);
    }

    using Iter = TypedColumn<StringType>::iterator;
    Iter start = column->begin();
    Iter end = column->end();

    for(auto it = start; it != end; ++it)
    {
        std::cout << *it << std::endl;
    }
}

#endif // COMPARATORTEST_H
