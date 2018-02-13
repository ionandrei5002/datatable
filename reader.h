#ifndef READER_H
#define READER_H

#include <string>
#include <vector>
#include <chrono>
#include <experimental/string_view>
#include <fstream>
#include <algorithm>

#include "values/value.h"
#include "schema.h"
#include "builders.h"

class Reader {
public:
    virtual ~Reader() {}
    virtual void initPrimitives() = 0;
    virtual void printPrimitives() = 0;
    virtual void read(std::vector<std::shared_ptr<Column>>& _columns, uint64_t* _size) = 0;
};

class CsvReader: public Reader {
private:
    std::string _file;
    Schema _schema;
    std::vector<std::shared_ptr<ViewerValue>> _primitives;
public:
    CsvReader(std::string& file, Schema& schema)
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
    void read(std::vector<std::shared_ptr<Column>>& _columns, uint64_t* _size) override
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

        start = std::chrono::high_resolution_clock::now();

        std::fstream input(this->_file);
        std::string line;
        line.reserve(1024 * 1024);

        std::vector<std::string> piece;

        bool hadException = false;

        std::getline(input, line);
        while(std::getline(input, line))
        {
            split(piece, line, ',');
            for(size_t i = 0; i < _primitives.size(); i++)
            {
                try {
                    std::string* value = &piece.at(i);
                    _primitives.at(i)->cast(value);
                } catch(std::exception& ex)
                {
                    std::cout << __FILE__ << __LINE__ << ex.what() << " " << line << std::endl;
                    hadException = true;
                    break;
                }
            }

            if (hadException == false)
            {
                for(size_t i = 0; i < _primitives.size(); i++)
                {
                    ViewerByteBuffer value = _primitives.at(i)->get();
                    _columns.at(i)->putValue(value);
                }
                (*_size)++;
            }

            hadException = false;
            piece.clear();
        }

        input.close();

        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end - start;

        std::cout << "read duration = " << elapsed_time.count() << "s" << std::endl;
    }
    void split(std::vector<std::string>& results, std::string const& original, char separator)
    {
        std::string::const_iterator start = original.begin();
        std::string::const_iterator end = original.end();
        std::string::const_iterator next = std::find(start, end, separator);
        while(next != end && *start == '"' && *(next-1) != '"')
        {
            next = find(next + 1, end, separator);
        }
        while (next != end) {
            std::string str(start.operator ->(), static_cast<uint64_t>(next.operator ->() - start.operator ->()));
            results.push_back(str);

            start = next + 1;
            next = std::find(start, end, separator);
            while(*start == '"' && *(next-1) != '"' && next != end)
            {
                next = find(next + 1, end, separator);
            }
        }

        std::string str(start.operator ->(), static_cast<uint64_t>(next.operator ->() - start.operator ->()));
        results.push_back(str);
    }
};

#endif // READER_H
