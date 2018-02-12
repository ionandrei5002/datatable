#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "../types.h"
#include "../column.h"

class Comparator {
public:
    Comparator(Column* column, Comparator* children):_sort(Sort(column, children)) {}
    virtual ~Comparator() {}
    virtual void set(ViewerValue* lv) = 0;
    virtual bool operator<(ViewerValue* rv) = 0;
    virtual bool operator>(ViewerValue* rv) = 0;
    virtual bool operator==(ViewerValue* rv) = 0;
    virtual bool operator!=(ViewerValue* rv) = 0;
    virtual bool operator()(ViewerValue* lv, ViewerValue* rv) = 0;
    struct Sort
    {
    private:
        Column* _column = nullptr;
        Comparator* _children = nullptr;
    public:
        Sort(Column* column, Comparator* children):_column(column),_children(children) {}
        bool operator()(uint64_t lv, uint64_t rv)
        {
            ViewerValue* vlv = _column->getValue(lv);
            ViewerValue* vrv = _column->getValue(rv);
            return _children->operator ()(vlv, vrv);
        }
    } _sort;
};

template<typename T>
class TypedComparator: public Comparator
{
private:
    ViewerValue* _lv;
public:
    TypedComparator(Column* column):Comparator(column, this) {}
    void set(ViewerValue* lv) override
    {
        _lv = lv;
    }
    bool operator<(ViewerValue* rv) override
    {
        return (*static_cast<TypedViewerValue<T>*>(_lv)) < (*static_cast<TypedViewerValue<T>*>(rv));
    }
    bool operator>(ViewerValue* rv) override
    {
        return (*static_cast<TypedViewerValue<T>*>(_lv)) > (*static_cast<TypedViewerValue<T>*>(rv));
    }
    bool operator==(ViewerValue* rv) override
    {
        return (*static_cast<TypedViewerValue<T>*>(_lv)) == (*static_cast<TypedViewerValue<T>*>(rv));
    }
    bool operator!=(ViewerValue* rv) override
    {
        return (*static_cast<TypedViewerValue<T>*>(_lv)) != (*static_cast<TypedViewerValue<T>*>(rv));
    }
    bool operator()(ViewerValue* lv, ViewerValue* rv) override
    {
        std::cout << *lv << " " << *rv << std::endl;
        return (*static_cast<TypedViewerValue<T>*>(lv)) < (*static_cast<TypedViewerValue<T>*>(rv));
    }
};

#endif // COMPARATOR_H
