#include <iostream>
#include <string>
#include "schema.h"
#include "table.h"

#include "builders.h"

int main()
{
    Schema schema;
    schema.push(Node(std::string("udid"), Type::INT64, Encoding::PLAIN, false))
            .push(Node(std::string("date"), Type::STRING, Encoding::PLAIN, false));

    Table table(std::string("iron_blade_dau"), schema);
    table.initColumns();

    std::string inFile("/home/andrei/Desktop/IronBladeDau.csv");
    table.readCsv(inFile);

    std::cout << "table size: " << table.size() << std::endl;

    std::string outFile("/home/andrei/Desktop/output.csv");
    table.writeCsv(outFile);

    return 0;
}
