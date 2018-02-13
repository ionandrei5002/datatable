#ifndef TABLE_H
#define TABLE_H

#include "types.h"
#include "schema.h"
#include "reader.h"
#include "writer.h"
#include "column.h"

#include <iostream>
#include <string>

class Table {
private:
    Reader* _reader = nullptr;
    Writer* _writer = nullptr;
    std::string _name;
    Schema _schema;
    std::vector<std::shared_ptr<Column>> _columns;
    uint64_t _size = 0;
    std::vector<uint64_t> _order;
public:
    Table(std::string name, Schema schema):_name(name),_schema(schema),_order(std::vector<uint64_t>()) {}
    friend std::ostream& operator <<(std::ostream& out, const Table& table)
    {
        out << "table " << table._name << "\n" << table._schema;

        return out;
    }
    void initColumns()
    {
        uint64_t columns = _schema.size();
        for(uint64_t i = 0; i < columns; i++)
        {
            Node node = _schema.peek(i);
            std::shared_ptr<Column> column = ColumnBuilder(node);
            _columns.push_back(column);
        }
    }
    uint64_t size()
    {
        return this->_size;
    }
    void readCsv(std::string& file)
    {
        _reader = new CsvReader(file, this->_schema);
        _reader->initPrimitives();
        _reader->printPrimitives();
        _reader->read(this->_columns, &this->_size);

        for(uint64_t rec = 0; rec < _size; rec++)
        {
            _order.push_back(rec);
        }

        delete _reader;
        _reader = nullptr;
    }
    void writeCsv(std::string& file)
    {
        _writer = new CsvWriter(file, this->_schema);
        _writer->initPrimitives();
        _writer->printPrimitives();
        _writer->write(this->_columns, this->_order);

        delete _writer;
        _writer = nullptr;
    }
    void sortTable(std::vector<std::string> columns)
    {
        std::vector<uint64_t> cols;
        for(auto it = columns.begin(); it != columns.end(); ++it)
        {
            cols.push_back(_schema.position(*it));
        }

        this->sortTable(cols);
    }
    void sortTable(std::vector<uint64_t> columns)
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

        start = std::chrono::high_resolution_clock::now();

        for(auto it = columns.rbegin(); it != columns.rend(); ++it)
        {
            uint64_t i = *it;
            Node node = this->_schema.peek(i);
            std::shared_ptr<Comparator> comp = ComparatorBuilder(this->_columns.at(i).get(), node);
            std::stable_sort(_order.begin(), _order.end(), comp->_sort);
        }

        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end - start;

        std::cout << "sort duration = " << elapsed_time.count() << "s" << std::endl;
    }
};

#endif // TABLE_H
