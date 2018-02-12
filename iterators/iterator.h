#ifndef ITERATOR_H
#define ITERATOR_H

#include <iterator>

#include "../column.h"

template<typename T>
class TypedColumn;

template<typename T>
class ColumnIterator: public std::iterator<std::random_access_iterator_tag, TypedViewerValue<T>>
{
public:
    // Iterator traits, previously from std::iterator.
    using value_type = TypedViewerValue<T>;
    using difference_type = typename std::iterator<std::random_access_iterator_tag, TypedViewerValue<T>>::difference_type;
    using pointer = TypedViewerValue<T>*;
    using reference = TypedViewerValue<T>&;
    using iterator_category = std::random_access_iterator_tag;

    // Default constructible.
    ColumnIterator() {}
    explicit ColumnIterator(uint64_t current, TypedColumn<T>* column):_current(current),_column(column) {}

    inline ColumnIterator& operator+=(difference_type rhs) {_current += rhs; return *this;}
    inline ColumnIterator& operator-=(difference_type rhs) {_current -= rhs; return *this;}
    inline reference operator*() const {return *static_cast<TypedViewerValue<T>*>(_column->getValue(_current));}
    inline pointer operator->() const {return static_cast<TypedViewerValue<T>*>(_column->getValue(_current));;}
    inline reference operator[](difference_type rhs) const {return *static_cast<TypedViewerValue<T>*>(_column->getValue(rhs));}

    inline ColumnIterator& operator++() {++_current; return *this;}
    inline ColumnIterator& operator--() {--_current; return *this;}
    inline ColumnIterator operator++(int) const {ColumnIterator tmp(*this); ++tmp._current; return tmp;}
//    inline ColumnIterator operator--(int) const {ColumnIterator tmp(*this); --tmp._current; return tmp;}
    inline difference_type operator+(const ColumnIterator& rhs) {return _current+rhs._current;}
    inline difference_type operator-(const ColumnIterator& rhs) const {return _current-rhs._current;}
    inline ColumnIterator operator+(difference_type rhs) const {return ColumnIterator(_current+rhs, _column);}
    inline ColumnIterator operator-(difference_type rhs) const {return ColumnIterator(_current-rhs, _column);}
//    friend inline ColumnIterator operator+(difference_type lhs, const ColumnIterator& rhs) {return ColumnIterator(lhs+rhs._current, rhs._column);}
//    friend inline ColumnIterator operator-(difference_type lhs, const ColumnIterator& rhs) {return ColumnIterator(lhs-rhs._current, rhs._column);}

    inline bool operator==(const ColumnIterator& rhs) const {return _column->getValue(_current) == rhs._column->getValue(rhs._current);}
    inline bool operator!=(const ColumnIterator& rhs) const {return _column->getValue(_current) != rhs._column->getValue(rhs._current);}
    inline bool operator>(const ColumnIterator& rhs) const {return _column->getValue(_current) > rhs._column->getValue(rhs._current);}
    inline bool operator<(const ColumnIterator& rhs) const {return _column->getValue(_current) < rhs._column->getValue(rhs._current);}
    inline bool operator>=(const ColumnIterator& rhs) const {return _column->getValue(_current) >= rhs._column->getValue(rhs._current);}
    inline bool operator<=(const ColumnIterator& rhs) const {return _column->getValue(_current) <= rhs._column->getValue(rhs._current);}
private:
    uint64_t _current {0};
    TypedColumn<T>* _column = nullptr;
};

#endif // ITERATOR_H
