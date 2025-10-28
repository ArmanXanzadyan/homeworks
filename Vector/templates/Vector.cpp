///  =============================================VECTOR========================================================================== 
#include "../headers/Vector.hpp"
#include <cstddef>
#include <cmath>
#include <iostream>
#include <ostream>
#include <cstring>

template <typename T>
Vector<T>::Vector()
    : begin_(NULL)
    , end_(NULL)
    , bufferEnd_(NULL)
{}

template <typename T>
Vector<T>::Vector(const size_type size, const_reference value)
    : begin_(NULL)
    , end_(NULL)
    , bufferEnd_(NULL)
{
    resize(size, value);
}

template <typename T>
Vector<T>::Vector(const int size, const_reference value)
    : begin_(NULL)
    , end_(NULL)
    , bufferEnd_(NULL)
{
    resize(size, value);
}

template <typename T>
template <typename InputIterator>
Vector<T>::Vector(InputIterator first, InputIterator last)
    : begin_(NULL)
    , end_(NULL)
    , bufferEnd_(NULL)

{
    reserve(last - first);
    insert(begin(), first, last);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& rhv)
    : begin_(NULL)
    , end_(NULL)
    , bufferEnd_(NULL)
{
    const size_type newSize = rhv.size();
    resize(newSize);
    for (size_type i = 0; i < newSize; ++i) {
        begin_[i] = rhv.begin_[i];
    }
}

template <typename T>
Vector<T>::~Vector()
{
    clear();
}

template <typename T>
Vector<T>&
Vector<T>::operator=(const Vector<T>& rhv)
{
    if (this != &rhv) {
        const size_type newSize = rhv.size();
        resize(newSize);
        for (size_type i = 0; i < newSize; ++i) {
            begin_[i] = rhv.begin_[i];
        }
    }
    return *this;
}

template <typename T>
typename Vector<T>::reference
Vector<T>::operator[](const size_type index)
{
    assert(index < size());
    return begin_[index];
}

template <typename T>
typename Vector<T>::const_reference
Vector<T>::operator[](const size_type index) const
{
    assert(index < size());
    return begin_[index];
}

template <typename T>
void*
Vector<T>::operator new(const size_type size)
{
    return ::operator new(size);
}

template <typename T>
void
Vector<T>::operator delete(void* ptr)
{
    ::operator delete(ptr);
}

template <typename T>
void*
Vector<T>::operator new[](const size_type size)
{
    return ::operator new[](size);
}

template <typename T>
void
Vector<T>::operator delete[](void* ptr)
{
    ::operator delete[](ptr);
}

template <typename T>
bool
Vector<T>::operator==(const Vector<T>& rhv) const
{
    if (this == &rhv)         return true;
    if (size() != rhv.size()) return false;

    for (size_type i = 0; i < size(); ++i) {
        if (begin_[i] != rhv.begin_[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool
Vector<T>::operator!=(const Vector<T>& rhv) const
{
    return !(*this == rhv);
}

template <typename T>
bool
Vector<T>::operator<(const Vector<T>& rhv) const
{
    return lexicographical_compare(begin(), end(), rhv.begin(), rhv.end());
}

template <typename T>
bool
Vector<T>::operator>(const Vector<T>& rhv) const
{
    return !(*this == rhv || *this < rhv);
}

template <typename T>
bool
Vector<T>::operator<=(const Vector<T>& rhv) const
{
    return !(*this > rhv);
}

template <typename T>
bool
Vector<T>::operator>=(const Vector<T>& rhv) const
{
    return !(*this < rhv);
}

template <typename T>
void
Vector<T>::push_back(const_reference value)
{
    if (end_ == bufferEnd_) {
        const size_type currentSize = size();
        const size_type newCapacity = ((0 == currentSize) ? 1 : static_cast<size_type>(std::ceil(currentSize * RESERVE_COEFFICIENT)));
        reserve(newCapacity);
    }
    *end_ = value;
    ++end_;
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::insert(iterator position, const_reference initialValue)
{
    assert(position >= begin() && position <= end());
    const difference_type index = position - begin();
    
    reserve(size() + 1);
    position = begin() + index;

    ++end_;
    shiftToEnd(position, 1);
    *position = initialValue;
    return position;
}

template <typename T>
void
Vector<T>::insert(iterator position, size_type count, const_reference initialValue)
{
    assert(position >= begin() && position <= end());
    for (size_type i = 0; i < count; ++i) {
        position = insert(position, initialValue);
    }
}

template <typename T>
void
Vector<T>::insert(iterator position, const int count, const_reference initialValue)
{
    assert(position >= begin() && position <= end());
    for (int i = 0; i < count; ++i) {
        position = insert(position, initialValue);
    }
}

template <typename T>
template <typename InputIterator>
void
Vector<T>::insert(iterator position, InputIterator first, InputIterator last)
{
    assert(position >= begin() && position <= end());
    while (first != last) {
        position = insert(position, *first);
        ++first;
        ++position;
    }
}

template <typename T>
void
Vector<T>::shiftToEnd(iterator position, const size_type count)
{
    for (iterator i = end() - 1; i >= position + count; --i) {
        *i = *(i - count);
        if (i == position) break; 
    }
}

template <typename T>
void
Vector<T>::pop_back()
{
    assert(!empty());
    --end_;
    end_->~T();
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::erase(iterator first, iterator last)
{
    while (first != last) {
        first = erase(first);
        --last;
    }
    return first;
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::erase(iterator position)
{
    assert(position >= begin() && position <= end());
    shiftToLeft(position, 1);
    --end_;
    return position;
}

template <typename T>
void
Vector<T>::shiftToLeft(iterator position, const size_type count)
{
    for (iterator i = position; i != end() - count; ++i) {
        *i = *(i + count);
    }
}

template <typename T>
void
Vector<T>::swap(Vector<T>& rhv)
{
    const Vector<T> temp = this;
    this = rhv;
    rhv = temp;
}

template <typename T>
void
Vector<T>::sort()
{
    if (size() < 2) return;
    const size_type newSize = size() - 1;

    for (size_type i = 0; i < newSize; ++i) {
        size_type k = 0;
        for (size_type j = 0; j < newSize - i; ++j) {
            if (begin_[j] > begin_[j + 1]) {
                std::swap(begin_[j], begin_[j + 1]);
                ++k;
            }
        }
        if (0 == k) break;
    }
}

template <typename T>
void
Vector<T>::resize(const size_type newSize, const_reference initialValue)
{
    const size_type previousSize = size();
    if (previousSize != newSize) {
        reserve(newSize);
        for (size_type i = previousSize; i < newSize; ++i) {
            begin_[i] = initialValue;
        }
        for (size_type i = newSize; i < previousSize; ++i) {
            begin_[i].~T();
        }
    }
    end_ = begin_ + newSize;
}

template <typename T>
void
Vector<T>::reserve(size_type newCapacity)
{
    if (newCapacity > capacity()) {
        void* rawMemory = ::operator new(sizeof(T) * newCapacity);
        T* newPtr = static_cast<T*>(rawMemory);

        const size_type previousSize = size();

        for (size_type i = 0; i < previousSize; ++i) {
            new(newPtr + i) T(begin_[i]);
        }

        for (size_type i = 0; i < previousSize; ++i) {
            begin_[i].~T();
        }

        ::operator delete(begin_);

        begin_ = newPtr;
        end_ = newPtr + previousSize;
        bufferEnd_ = newPtr + newCapacity;
    }
}

template <typename T>
typename Vector<T>::const_iterator
Vector<T>::begin() const
{
    return const_iterator(begin_);
}

template <typename T>
typename Vector<T>::const_iterator
Vector<T>::end() const
{
    return const_iterator(end_); 
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::begin() 
{
    return iterator(begin_);
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::end()
{
    return iterator(end_); 
}

template <typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::rbegin() const
{
    return const_reverse_iterator(end_ - 1);
}

template <typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::rend() const
{
    return const_reverse_iterator(begin_ - 1); 
}

template <typename T>
typename Vector<T>::reverse_iterator
Vector<T>::rbegin() 
{
    return reverse_iterator(end_ - 1);
}

template <typename T>
typename Vector<T>::reverse_iterator
Vector<T>::rend()
{
    return reverse_iterator(begin_ - 1); 
}

template <typename T>
typename Vector<T>::size_type
Vector<T>::size() const
{
    return end_ - begin_;  
}

template <typename T>
typename Vector<T>::size_type
Vector<T>::capacity() const
{
    return bufferEnd_ - begin_;
}

template <typename T>
bool
Vector<T>::empty() const
{
    return begin_ == end_; 
}

template <typename T>
void
Vector<T>::clear()
{
    if (NULL != begin_) {
        delete[] begin_;
        begin_ =     NULL;
        end_ =       NULL;
        bufferEnd_ = NULL;
    }
}

template <typename T>
typename Vector<T>::size_type
Vector<T>::max_size() const
{
    return size_t(-1) / sizeof(T);;
}

template <typename T>
template <class InputIt1, class InputIt2>
bool
Vector<T>::lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
        if (*first1 < *first2) return true; 
        if (*first2 < *first1) return false; 
    }
    return (first1 == last1) && (first2 != last2);
}

/// ===========================================CONST_ITERATOR==================================

template <typename T>
Vector<T>::const_iterator::const_iterator()
    : ptr_(NULL)
{}

template <typename T>
Vector<T>::const_iterator::const_iterator(const const_iterator& rhv)
    : ptr_(rhv.ptr_)
{}

template <typename T>
Vector<T>::const_iterator::~const_iterator()
{
    ptr_ = NULL;
}

template <typename T>
Vector<T>::const_iterator::const_iterator(pointer ptr)
    : ptr_(ptr)
{}

template <typename T>
typename Vector<T>::pointer
Vector<T>::const_iterator::getPtr() const
{
    return ptr_;
}

template <typename T>
typename Vector<T>::const_iterator&
Vector<T>::const_iterator::operator=(const const_iterator& rhv)
{
    ptr_ = rhv.ptr_;
    return *this;
}

template <typename T>
typename Vector<T>::const_reference
Vector<T>::const_iterator::operator*() const
{
    return *ptr_;
}

template <typename T>
typename Vector<T>::pointer
Vector<T>::const_iterator::operator->() const
{
    return ptr_;
}

template <typename T>
typename Vector<T>::const_reference
Vector<T>::const_iterator::operator[](const size_type index) const
{
    assert(ptr_ != NULL);
    return *(ptr_ + index); 
}

template <typename T>
typename Vector<T>::const_iterator&
Vector<T>::const_iterator::operator++()
{
    ++ptr_;
    return *this;
}

template <typename T>
typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator++(int)
{
    const_iterator temp(*this);
    ++ptr_;
    return temp;
}

template <typename T>
typename Vector<T>::const_iterator&
Vector<T>::const_iterator::operator--()
{
    --ptr_;
    return *this;
}

template <typename T>
typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator--(int)
{
    const_iterator temp(*this);
    --ptr_;
    return temp;
}

template <typename T>
typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator+(const size_type size) const
{
    return const_iterator(ptr_ + size);    
}

template <typename T>
typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator-(const size_type index) const
{
    return const_iterator(ptr_ - index);    
}

template <typename T>
typename Vector<T>::const_iterator&
Vector<T>::const_iterator::operator+=(const size_type size)
{
    ptr_ += size; 
    return *this;
}

template <typename T>
typename Vector<T>::const_iterator&
Vector<T>::const_iterator::operator-=(const size_type size)
{
    ptr_ -= size; 
    return *this;
}

template <typename T>
bool
Vector<T>::const_iterator::operator==(const const_iterator& rhv) const
{
    return ptr_ == rhv.ptr_; 
}

template <typename T>
bool
Vector<T>::const_iterator::operator!=(const const_iterator& rhv) const
{
    return !(*this == rhv); 
}

template <typename T>
bool
Vector<T>::const_iterator::operator<(const const_iterator& rhv) const
{
    return ptr_ < rhv.ptr_; 
}

template <typename T>
bool
Vector<T>::const_iterator::operator>(const const_iterator& rhv) const
{
    return !(*this == rhv || *this < rhv);
}
template <typename T>
bool
Vector<T>::const_iterator::operator<=(const const_iterator& rhv) const
{
    return !(*this > rhv);
}

template <typename T>
bool
Vector<T>::const_iterator::operator>=(const const_iterator& rhv) const
{
    return !(*this < rhv); 
}

/// ===========================================ITERATOR========================================

template <typename T>
Vector<T>::iterator::iterator()
    : const_iterator()
{}

template <typename T>
Vector<T>::iterator::iterator(const iterator& rhv)
    : const_iterator(rhv)
{}

template <typename T>
Vector<T>::iterator::~iterator()
{}

template <typename T>
Vector<T>::iterator::iterator(pointer ptr)
    : const_iterator(ptr)
{}

template <typename T>
typename Vector<T>::iterator&
Vector<T>::iterator::operator=(const iterator& rhv)
{
    const_iterator::operator=(rhv);
    return *this;
}

template <typename T>
typename Vector<T>::reference
Vector<T>::iterator::operator*() const
{
    return *(this->getPtr());
}

template <typename T>
typename Vector<T>::difference_type
Vector<T>::iterator::operator-(const iterator& rhv) const
{
    return this->getPtr() - rhv.getPtr();    
}

template <typename T>
typename Vector<T>::pointer
Vector<T>::iterator::operator->() const
{
    return this->getPtr();
}

template <typename T>
typename Vector<T>::reference
Vector<T>::iterator::operator[](const size_type index) const
{
    assert(this->getPtr() != NULL);
    return *(this->getPtr() + index); 
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::iterator::operator+(const size_type size) const
{
    return iterator(this->getPtr() + size);    
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::iterator::operator-(const size_type index) const
{
    return iterator(this->getPtr() - index);    
}

template <typename T>
bool
Vector<T>::iterator::operator==(const iterator& rhv) const
{
    return this->getPtr() == rhv.getPtr(); 
}

template <typename T>
bool
Vector<T>::iterator::operator!=(const iterator& rhv) const
{
    return !(*this == rhv); 
}

template <typename T>
bool
Vector<T>::iterator::operator<(const iterator& rhv) const
{
    return this->getPtr() < rhv.getPtr(); 
}

template <typename T>
bool
Vector<T>::iterator::operator>(const iterator& rhv) const
{
    return !(*this == rhv || *this < rhv);
}
template <typename T>
bool
Vector<T>::iterator::operator<=(const iterator& rhv) const
{
    return !(*this > rhv);
}

template <typename T>
bool
Vector<T>::iterator::operator>=(const iterator& rhv) const
{
    return !(*this < rhv); 
}

///====================================================CONST_REVERSE_ITERATOR======================


template <typename T>
Vector<T>::const_reverse_iterator::const_reverse_iterator()
    : ptr_(NULL)
{}

template <typename T>
Vector<T>::const_reverse_iterator::const_reverse_iterator(const const_reverse_iterator& rhv)
    : ptr_(rhv.ptr_)
{}

template <typename T>
Vector<T>::const_reverse_iterator::~const_reverse_iterator()
{
    ptr_ = NULL;
}

template <typename T>
Vector<T>::const_reverse_iterator::const_reverse_iterator(pointer ptr)
    : ptr_(ptr)
{}

template <typename T>
typename Vector<T>::pointer
Vector<T>::const_reverse_iterator::getPtr() const
{
    return ptr_;
}

template <typename T>
typename Vector<T>::const_reverse_iterator&
Vector<T>::const_reverse_iterator::operator=(const const_reverse_iterator& rhv)
{
    ptr_ = rhv.ptr_;
    return *this;
}

template <typename T>
typename Vector<T>::const_reference
Vector<T>::const_reverse_iterator::operator*() const
{
    return *ptr_;
}

template <typename T>
typename Vector<T>::pointer
Vector<T>::const_reverse_iterator::operator->() const 
{
    return ptr_;
}

template <typename T>
typename Vector<T>::const_reference
Vector<T>::const_reverse_iterator::operator[](const size_type index) const
{
    assert(ptr_ != NULL);
    return *(ptr_ - index); 
}

template <typename T>
typename Vector<T>::const_reverse_iterator&
Vector<T>::const_reverse_iterator::operator++()
{
    --ptr_;
    return *this;
}

template <typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator++(int)
{
    const_reverse_iterator temp(*this);
    --ptr_;
    return temp;
}

template <typename T>
typename Vector<T>::const_reverse_iterator&
Vector<T>::const_reverse_iterator::operator--()
{
    ++ptr_;
    return *this;
}

template <typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator--(int)
{
    const_reverse_iterator temp(*this);
    ++ptr_;
    return temp;
}

template <typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator+(const size_type size) const
{
    return const_reverse_iterator(ptr_ - size);    
}

template <typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator-(const size_type index) const
{
    return const_reverse_iterator(ptr_ + index);    
}

template <typename T>
typename Vector<T>::difference_type
Vector<T>::const_reverse_iterator::operator-(const const_reverse_iterator& rhv) const
{
    return this->getPtr() - rhv.getPtr();    
}

template <typename T>
typename Vector<T>::const_reverse_iterator&
Vector<T>::const_reverse_iterator::operator+=(const size_type size)
{
    ptr_ -= size; 
    return *this;
}

template <typename T>
typename Vector<T>::const_reverse_iterator&
Vector<T>::const_reverse_iterator::operator-=(const size_type size)
{
    ptr_ += size; 
    return *this;
}

template <typename T>
bool
Vector<T>::const_reverse_iterator::operator==(const const_reverse_iterator& rhv) const
{
    return ptr_ == rhv.ptr_; 
}

template <typename T>
bool
Vector<T>::const_reverse_iterator::operator!=(const const_reverse_iterator& rhv) const
{
    return !(*this == rhv); 
}

template <typename T>
bool
Vector<T>::const_reverse_iterator::operator<(const const_reverse_iterator& rhv) const
{
    return ptr_ < rhv.ptr_; 
}

template <typename T>
bool
Vector<T>::const_reverse_iterator::operator>(const const_reverse_iterator& rhv) const
{
    return !(*this == rhv || *this < rhv);
}
template <typename T>
bool
Vector<T>::const_reverse_iterator::operator<=(const const_reverse_iterator& rhv) const
{
    return !(*this > rhv);
}

template <typename T>
bool
Vector<T>::const_reverse_iterator::operator>=(const const_reverse_iterator& rhv) const
{
    return !(*this < rhv); 
}

///==============================================REVERSE_ITERATOR==============================

template <typename T>
Vector<T>::reverse_iterator::reverse_iterator()
    : const_reverse_iterator()
{}

template <typename T>
Vector<T>::reverse_iterator::reverse_iterator(const reverse_iterator& rhv)
    : const_reverse_iterator(rhv.getPtr())
{}

template <typename T>
Vector<T>::reverse_iterator::~reverse_iterator()
{}

template <typename T>
Vector<T>::reverse_iterator::reverse_iterator(pointer ptr)
    : const_reverse_iterator(ptr)
{}

template <typename T>
typename Vector<T>::reverse_iterator&
Vector<T>::reverse_iterator::operator=(const reverse_iterator& rhv)
{
    const_reverse_iterator::operator=(rhv); 
    return *this;
}

template <typename T>
typename Vector<T>::reference
Vector<T>::reverse_iterator::operator*() const
{
    return *(this->getPtr());
}

template <typename T>
typename Vector<T>::difference_type
Vector<T>::reverse_iterator::operator-(const reverse_iterator& rhv) const
{
    return this->getPtr() - rhv.getPtr();    
}

template <typename T>
typename Vector<T>::pointer
Vector<T>::reverse_iterator::operator->() const
{
    return this->getPtr();
}

template <typename T>
typename Vector<T>::reference
Vector<T>::reverse_iterator::operator[](const size_type index) const
{
    assert(this->getPtr() != NULL);
    return *(this->getPtr() - index); 
}

template <typename T>
typename Vector<T>::reverse_iterator
Vector<T>::reverse_iterator::operator+(const size_type size) const
{
    return reverse_iterator(this->getPtr() - size);    
}

template <typename T>
typename Vector<T>::reverse_iterator
Vector<T>::reverse_iterator::operator-(const size_type index) const
{
    return reverse_iterator(this->getPtr() + index);    
}

template <typename T>
bool
Vector<T>::reverse_iterator::operator==(const reverse_iterator& rhv) const
{
    return this->getPtr() == rhv.getPtr(); 
}

template <typename T>
bool
Vector<T>::reverse_iterator::operator!=(const reverse_iterator& rhv) const
{
    return !(*this == rhv); 
}

template <typename T>
bool
Vector<T>::reverse_iterator::operator<(const reverse_iterator& rhv) const
{
    return this->getPtr() < rhv.getPtr(); 
}

template <typename T>
bool
Vector<T>::reverse_iterator::operator>(const reverse_iterator& rhv) const
{
    return !(*this == rhv || *this < rhv);
}
template <typename T>
bool
Vector<T>::reverse_iterator::operator<=(const reverse_iterator& rhv) const
{
    return !(*this > rhv);
}

template <typename T>
bool
Vector<T>::reverse_iterator::operator>=(const reverse_iterator& rhv) const
{
    return !(*this < rhv); 
}

template <typename T1>
std::ostream&
operator<<(std::ostream& output, const Vector<T1>& rhv)
{
    output << "{ ";
    for (typename Vector<T1>::const_iterator i = rhv.begin(); i < rhv.end(); ++i) {
        output << *i << ' ';
    }
    output << '}';
    return output;
}

template <typename T1>
std::istream&
operator>>(std::istream& input, Vector<T1>& rhv)
{
    for (typename Vector<T1>::iterator i = rhv.begin(); i < rhv.end(); ++i) {
        input >> *i;
    }
    return input;
}

