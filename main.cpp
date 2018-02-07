#include <iostream>
#include <string>
#include "schema.h"
#include "table.h"

int main()
{
    Schema schema;
    schema.push(Node(std::string("a1"), Type::INT64, Encoding::PLAIN, false))
            .push(Node(std::string("a2"), Type::STRING, Encoding::DICTIONARY, true));

    std::cout << schema;

    Table table(std::string("test"), schema);

    std::cout << table;

    return 0;
}
