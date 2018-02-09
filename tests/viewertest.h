#ifndef VIEWERTEST_H
#define VIEWERTEST_H

#include "gtest.h"
#include "../viewers/value.h"

TEST(ViewerValues, Int64TypeComparations)
{
    TypedViewerValue<Int64Type> first;
    TypedViewerValue<Int64Type> second;

    std::string str1("199909");
    std::string str2("199909");

    first.cast(&str1);
    second.cast(&str2);

    EXPECT_EQ(false, (first < second));
    EXPECT_EQ(false, (first > second));
    EXPECT_EQ(true, (first == second));
    EXPECT_EQ(false, (first != second));
}

TEST(ViewerValues, StringTypeComparations)
{
    TypedViewerValue<StringType> first;
    TypedViewerValue<StringType> second;

    std::string str1("199909");
    std::string str2("199909");

    first.cast(&str1);
    second.cast(&str2);

    EXPECT_EQ(false, (first < second));
    EXPECT_EQ(false, (first > second));
    EXPECT_EQ(true, (first == second));
    EXPECT_EQ(false, (first != second));
}


#endif // VIEWERTEST_H
