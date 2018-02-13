#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "../types.h"
#include "../column.h"

class Comparator {
public:
    Comparator() = delete;
    Comparator(Column* column):_sort(Sort(column, this)) {}
    Comparator(const Comparator& ot):_sort(Sort(ot._sort._column, ot._sort._children)) {}
    Comparator& operator=(const Comparator& ot)
    {
        this->_sort = Sort(ot._sort._column, ot._sort._children);
        return *this;
    }
    Comparator(Comparator&& ot):_sort(Sort(ot._sort._column, ot._sort._children)) {}
    Comparator& operator=(Comparator&& ot) = delete;
    virtual ~Comparator() {}
    virtual Type::type getType() = 0;
    virtual void set(ViewerByteBuffer lv) = 0;
    virtual bool operator<(ViewerByteBuffer& rv) = 0;
    virtual bool operator>(ViewerByteBuffer& rv) = 0;
    virtual bool operator==(ViewerByteBuffer& rv) = 0;
    virtual bool operator!=(ViewerByteBuffer& rv) = 0;
    virtual bool operator()(const ViewerByteBuffer& lv, const ViewerByteBuffer& rv) = 0;
    struct Sort
    {
    public:
        Column* _column = nullptr;
        Comparator* _children = nullptr;
    public:
        Sort() = delete;
        Sort(Column* column, Comparator* children):_column(column),_children(children) {}
        Sort(const Sort& ot)
        {
            _column =  ot._column;
            _children = ot._children;
        }
        Sort& operator=(const Sort& ot)
        {
            _column =  ot._column;
            _children = ot._children;

            return *this;
        }
        Sort(Sort&& ot)
        {
            _column =  ot._column;
            _children = ot._children;
        }
        Sort& operator=(Sort&& ot)
        {
            _column =  ot._column;
            _children = ot._children;

            return *this;
        }
        bool operator()(const uint64_t lv, const uint64_t rv)
        {
            ViewerByteBuffer vlv = _column->getValue(lv);
            ViewerByteBuffer vrv = _column->getValue(rv);

            return _children->operator ()(vlv, vrv);
        }
    } _sort;
};

template<typename T>
class TypedComparator: public Comparator
{
private:
    ViewerByteBuffer _lv;
public:
    TypedComparator() = delete;
    TypedComparator(Column* column):Comparator(column) {}
    TypedComparator(const TypedComparator<T>& oth):Comparator(oth._sort._column) {}
    TypedComparator& operator=(const TypedComparator<T>& oth) = delete;
    Type::type getType() override
    {
        return T::type_num;
    }
    void set(ViewerByteBuffer lv) override
    {
        _lv = lv;
    }
    bool operator<(ViewerByteBuffer& rv) override
    {
        TypedViewerValue<T> tlv;
        tlv.set(_lv);

        TypedViewerValue<T> trv;
        trv.set(rv);

        return tlv < trv;
    }
    bool operator>(ViewerByteBuffer& rv) override
    {
        TypedViewerValue<T> tlv;
        tlv.set(_lv);

        TypedViewerValue<T> trv;
        trv.set(rv);

        return tlv > trv;
    }
    bool operator==(ViewerByteBuffer& rv) override
    {
        TypedViewerValue<T> tlv;
        tlv.set(_lv);

        TypedViewerValue<T> trv;
        trv.set(rv);

        return tlv == trv;
    }
    bool operator!=(ViewerByteBuffer& rv) override
    {
        TypedViewerValue<T> tlv;
        tlv.set(_lv);

        TypedViewerValue<T> trv;
        trv.set(rv);

        return tlv != trv;
    }
    bool operator()(const ViewerByteBuffer& lv, const ViewerByteBuffer& rv) override
    {
        TypedViewerValue<T> tlv;
        TypedViewerValue<T> trv;

        tlv.set(lv);
        trv.set(rv);

        return tlv < trv;
    }
};

#endif // COMPARATOR_H
