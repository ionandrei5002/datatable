#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "../types.h"
#include "../viewers/value.h"

class Comparator
{
public:
    virtual ~Comparator() {}
};
template<typename T>
class TypedComparator
{
private:
    TypedViewerValue<T> _lv;
public:
    TypedComparator() {}
    void set(const TypedViewerValue<T>& lv)
    {
        _lv = lv;
    }
    bool operator<(const TypedViewerValue<T>& rv)
    {
        return _lv < rv;
    }
    bool operator>(const TypedViewerValue<T>& rv)
    {
        return _lv > rv;
    }
    bool operator==(const TypedViewerValue<T>& rv)
    {
        return _lv == rv;
    }
    bool operator!=(const TypedViewerValue<T>& rv)
    {
        return _lv != rv;
    }
    bool operator()(TypedViewerValue<T>& lv, TypedViewerValue<T>& rv)
    {
        return lv < rv;
    }
};

#endif // COMPARATOR_H
