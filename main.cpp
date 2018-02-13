#include <iostream>
#include <string>
#include "schema.h"
#include "table.h"

#include "builders.h"

//#include "comparators/comparator.h"

//#include "gtest.h"
//#include "tests/viewertest.h"
//#include "tests/comparatortest.h"
//#include "tests/columntest.h"

int main(int argc, char **argv)
{
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();

    Schema schema;
    schema.push(Node(std::string("a1"), Type::INT64, Encoding::PLAIN, false))
            .push(Node(std::string("a2"), Type::STRING, Encoding::PLAIN, false));
//    schema.push(Node(std::string("a1"), Type::STRING, Encoding::PLAIN, false))
//            .push(Node(std::string("a2"), Type::STRING, Encoding::PLAIN, false))
//            .push(Node(std::string("a3"), Type::INT32, Encoding::PLAIN, false))
//            .push(Node(std::string("a4"), Type::INT32, Encoding::PLAIN, false))
//            .push(Node(std::string("a5"), Type::INT32, Encoding::PLAIN, false))
//            .push(Node(std::string("a6"), Type::INT32, Encoding::PLAIN, false))
//            .push(Node(std::string("a7"), Type::INT32, Encoding::PLAIN, false))
//            .push(Node(std::string("a8"), Type::INT32, Encoding::PLAIN, false))
//            .push(Node(std::string("a9"), Type::INT32, Encoding::PLAIN, false))
//            .push(Node(std::string("a10"), Type::INT32, Encoding::PLAIN, false))
//            .push(Node(std::string("a11"), Type::STRING, Encoding::PLAIN, false))
//            .push(Node(std::string("a12"), Type::STRING, Encoding::PLAIN, false))
//            .push(Node(std::string("a13"), Type::STRING, Encoding::PLAIN, false))
//            .push(Node(std::string("a14"), Type::INT32, Encoding::PLAIN, false))
//            .push(Node(std::string("a15"), Type::STRING, Encoding::PLAIN, false))
//            .push(Node(std::string("a16"), Type::STRING, Encoding::PLAIN, false))
//            .push(Node(std::string("a17"), Type::STRING, Encoding::PLAIN, false))
//            .push(Node(std::string("a18"), Type::INT32, Encoding::PLAIN, false));

    Table table(std::string("dataset"), schema);
    table.initColumns();

    std::string inFile("/home/andrei/Desktop/MC5Lau.csv");
    table.readCsv(inFile);

    std::cout << "table size: " << table.size() << std::endl;

    table.sortTable(std::vector<uint64_t>({0,1}));

    std::string outFile("/home/andrei/Desktop/output.csv");
    table.writeCsv(outFile);

    return 0;
}
