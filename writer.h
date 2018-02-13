#ifndef WRITER_H
#define WRITER_H

#include "values/value.h"
#include "schema.h"
#include "builders.h"

class Writer {
public:
    virtual ~Writer() {}
    virtual void initPrimitives() = 0;
    virtual void printPrimitives() = 0;
    virtual void write(std::vector<std::shared_ptr<Column>>& _columns, std::vector<uint64_t>& _order) = 0;
};

class CsvWriter: public Writer {
private:
    std::string _file;
    Schema _schema;
    std::vector<std::shared_ptr<ViewerValue>> _primitives;
public:
    CsvWriter(std::string& file, Schema& schema)
        :_file(file),
        _schema(schema),
        _primitives(std::vector<std::shared_ptr<ViewerValue>>()) {}
    void initPrimitives() override
    {
        uint64_t columns = _schema.size();
        for(uint64_t i = 0; i < columns; i++)
        {
            Node node = _schema.peek(i);
            _primitives.push_back(ViewerValueBuilder(node));
        }
    }
    void printPrimitives() override
    {
        uint64_t columns = _schema.size();
        for(uint64_t i = 0; i < columns; i++)
        {
            Node node = _schema.peek(i);
            std::shared_ptr<ViewerValue> primitive = _primitives.at(i);

            std::cout << node << " ";
            primitive->print(std::cout);
            std::cout << std::endl;
        }
    }
    void write(std::vector<std::shared_ptr<Column>>& _columns, std::vector<uint64_t>& _order) override
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

        start = std::chrono::high_resolution_clock::now();

        std::ofstream out(this->_file);
        uint64_t columns = _primitives.size();

        for(uint64_t i : _order)
        {
            for(uint64_t j = 0; j < columns - 1; j++)
            {
                ViewerByteBuffer value = _columns[j]->getValue(i);
                ViewerValue* typed = _primitives.at(j).get();
                typed->set(value);
                out << *typed << ",";
            }
            ViewerByteBuffer value = _columns[columns - 1]->getValue(i);
            ViewerValue* typed = _primitives.at(columns - 1).get();
            typed->set(value);
            out << *typed << std::endl;
        }

        out.close();

        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end - start;

        std::cout << "write duration = " << elapsed_time.count() << "s" << std::endl;
    }
};

#endif // WRITER_H
