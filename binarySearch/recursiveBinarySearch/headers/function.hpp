#ifndef __FUNCTION_HPP__
#define __FUNCTION_HPP__

template <typename InputIterator, typename key>
InputIterator
binarySearch(InputIterator first, InputIterator last, const key& value);

#include "../templates/function.cpp"

#endif /// __FUNCTION_HPP__

