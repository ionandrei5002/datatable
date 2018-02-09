#ifndef COMPARATORTEST_H
#define COMPARATORTEST_H

#include "gtest.h"
#include "../comparators/comparator.h"

#include <vector>
#include <algorithm>

TEST(Comparators, Int64TypeComparations)
{
    TypedViewerValue<Int64Type> first;
    TypedViewerValue<Int64Type> second;

    std::string str1("199909");
    std::string str2("199909");

    first.cast(&str1);
    second.cast(&str2);

    TypedComparator<Int64Type> comparator;
    comparator.set(first);

    EXPECT_EQ(false, comparator.operator<(second));
    EXPECT_EQ(true, comparator.operator==(second));
    EXPECT_EQ(false, comparator.operator>(second));
    EXPECT_EQ(false, comparator.operator!=(second));
}

TEST(Comparators, StringTypeComparations)
{
    TypedViewerValue<StringType> first;
    TypedViewerValue<StringType> second;

    std::string str1("199909");
    std::string str2("199909");

    first.cast(&str1);
    second.cast(&str2);

    TypedComparator<StringType> comparator;
    comparator.set(first);

    EXPECT_EQ(false, comparator.operator<(second));
    EXPECT_EQ(true, comparator.operator==(second));
    EXPECT_EQ(false, comparator.operator>(second));
    EXPECT_EQ(false, comparator.operator!=(second));
}

TEST(Comparators, Sorter)
{
    std::vector<std::string> values {"10","4","3","11","7","6"};
    std::vector<TypedViewerValue<Int64Type>> toSort;
    for(auto it = values.begin(); it != values.end(); ++it)
    {
        TypedViewerValue<Int64Type> typed;
        typed.cast(&(*it));
        toSort.push_back(typed);
    }

    TypedComparator<Int64Type> comparator;
    std::sort(toSort.begin(), toSort.end(), comparator);

    TypedViewerValue<Int64Type> comp;

    comp.cast(&values[2]);
    EXPECT_EQ(true, (comp == toSort[0]));
    comp.cast(&values[1]);
    EXPECT_EQ(true, (comp == toSort[1]));
    comp.cast(&values[5]);
    EXPECT_EQ(true, (comp == toSort[2]));
    comp.cast(&values[4]);
    EXPECT_EQ(true, (comp == toSort[3]));
    comp.cast(&values[0]);
    EXPECT_EQ(true, (comp == toSort[4]));
    comp.cast(&values[3]);
    EXPECT_EQ(true, (comp == toSort[5]));
}

#endif // COMPARATORTEST_H
