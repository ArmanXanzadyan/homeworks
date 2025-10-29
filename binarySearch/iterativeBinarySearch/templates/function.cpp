#include "../headers/function.hpp"
#include <cstddef>
#include <iterator>


template <typename InputIterator, typename key>
InputIterator
binarySearch(InputIterator first, InputIterator last, const key& value)
{
    while (first != last) {
        typename std::iterator_traits<InputIterator>::difference_type dist = std::distance(first, last);
        InputIterator middle = first;
        std::advance(middle, dist / 2);
        if (value < *middle) {
            last = middle;
            continue;
        }
        if (value > *middle) {
            first = ++middle;
            continue;
        }
        return middle;
    }
    return last;
}

