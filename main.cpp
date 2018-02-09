#include <iostream>
#include <string>
#include "schema.h"
#include "table.h"

#include "builders.h"

#include "comparators/comparator.h"

#include "gtest.h"
#include "tests/viewertest.h"
#include "tests/comparatortest.h"

int main(int argc, char **argv)
{
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();

    Schema schema;
    schema.push(Node(std::string("udid"), Type::INT64, Encoding::PLAIN, false))
            .push(Node(std::string("date"), Type::STRING, Encoding::DICTIONARY, false));

    Table table(std::string("mc5_dau"), schema);
    table.initColumns();

    std::string inFile("/home/andrei/Desktop/MC5Lau.csv");
    table.readCsv(inFile);

    std::cout << "table size: " << table.size() << std::endl;

    std::string outFile("/home/andrei/Desktop/output.csv");
    table.writeCsv(outFile);

    return 0;
}
