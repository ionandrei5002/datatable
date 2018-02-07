#ifndef TABLE_H
#define TABLE_H

#include "types.h"
#include "schema.h"
#include "reader.h"
#include "writer.h"

#include <iostream>
#include <string>

class Table {
private:
    Reader* _reader;
    Writer* _writer;
    std::string _name;
    Schema _schema;
public:
    Table(std::string name, Schema schema):_name(name),_schema(schema) {}
    friend std::ostream& operator <<(std::ostream& out, const Table& table)
    {
        out << "table " << table._name << "\n" << table._schema;

        return out;
    }
};

#endif // TABLE_H
