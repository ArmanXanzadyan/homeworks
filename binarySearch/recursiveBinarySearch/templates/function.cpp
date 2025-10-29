#ifndef __FUNCTION_CPP__
#define __FUNCTION_CPP__

#include <iterator>
#include "../headers/function.hpp"

template <typename InputIterator, typename Key>
InputIterator
binarySearch(InputIterator first, InputIterator last, const Key& value)
{
    if (first == last) return last;
    typename std::iterator_traits<InputIterator>::difference_type dist = std::distance(first, last);
    InputIterator middle = first;
    std::advance(middle, dist / 2);
    if (value < *middle) return binarySearch(first, middle, value);
    if (value > *middle) return binarySearch(++middle, last, value);
    return middle;
}

#endif /// __FUNCTION_CPP__

