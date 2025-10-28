#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <cstdlib>
#include <cassert>
#include <iostream>
#include <ostream>

const double RESERVE_COEFFICIENT = 1.6;

template <typename T>
class Vector
{
    template <typename T1> 
    friend std::ostream& operator<<(std::ostream& output, const Vector<T1>& rhv);
    template <typename T1>
    friend std::istream& operator>>(std::istream& input, Vector<T1>& rhv);

public:
    typedef size_t         size_type;
    typedef T              value_type;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef T*             pointer;
    typedef std::ptrdiff_t difference_type;
                                            /// ====CONST_ITERATOR====
public:
    class const_iterator {
    friend class Vector<T>;
    public:
        const_iterator();
        const_iterator(const const_iterator& rhv);
        ~const_iterator();

        const_iterator& operator=(const const_iterator& rhv);    
        const_reference operator*()                            const;
        pointer         operator->()                           const;
        const_reference operator[](const size_type index)      const;
        const_iterator& operator++();
        const_iterator  operator++(int);
        const_iterator& operator--();
        const_iterator  operator--(int);
        const_iterator  operator+(const size_type size)        const;
        const_iterator  operator-(const size_type size)        const;
        const_iterator& operator+=(const size_type size);
        const_iterator& operator-=(const size_type size);
        bool            operator==(const const_iterator& rhv)  const;
        bool            operator!=(const const_iterator& rhv)  const;
        bool            operator<(const const_iterator& rhv)   const;
        bool            operator>(const const_iterator& rhv)   const;
        bool            operator<=(const const_iterator& rhv)  const;
        bool            operator>=(const const_iterator& rhv)  const;

    protected:
        pointer getPtr() const;

    private:
        explicit const_iterator(pointer ptr);

    private:
        pointer ptr_;
    };
                                        /// ====ITERATOR====
public:
    class iterator : public const_iterator {
    friend class Vector<T>;
    public:
        iterator();
        iterator(const iterator& rhv);
        ~iterator();
        
        iterator&       operator=(const iterator& rhv);    
        reference       operator*()                       const;
        difference_type operator-(const iterator& rhv)    const;
        pointer         operator->()                      const;
        reference       operator[](const size_type index) const;
        iterator        operator+(const size_type size)   const;
        iterator        operator-(const size_type size)   const;
        bool            operator==(const iterator& rhv)   const;
        bool            operator!=(const iterator& rhv)   const;
        bool            operator<(const iterator& rhv)    const;
        bool            operator>(const iterator& rhv)    const;
        bool            operator<=(const iterator& rhv)   const;
        bool            operator>=(const iterator& rhv)   const;

    private:
        explicit iterator(pointer ptr);
    };
                                        ///====CONST_REVERSE_ITERATOR====
public:
    class const_reverse_iterator {
    friend class Vector<T>;
    public:
        const_reverse_iterator();
        const_reverse_iterator(const const_reverse_iterator& rhv);
        ~const_reverse_iterator();

        const_reverse_iterator& operator=(const const_reverse_iterator& rhv);    
        const_reference         operator*()                                   const;
        pointer                 operator->()                                  const;
        const_reference         operator[](const size_type index)             const;
        const_reverse_iterator& operator++();
        const_reverse_iterator  operator++(int);
        const_reverse_iterator& operator--();
        const_reverse_iterator  operator--(int);
        const_reverse_iterator  operator+(const size_type size)               const;
        const_reverse_iterator  operator-(const size_type size)               const;
        difference_type         operator-(const const_reverse_iterator& rhv)  const;
        const_reverse_iterator& operator+=(const size_type size);
        const_reverse_iterator& operator-=(const size_type size);
        bool                    operator==(const const_reverse_iterator& rhv) const;
        bool                    operator!=(const const_reverse_iterator& rhv) const;
        bool                    operator<(const const_reverse_iterator& rhv)  const;
        bool                    operator>(const const_reverse_iterator& rhv)  const;
        bool                    operator<=(const const_reverse_iterator& rhv) const;
        bool                    operator>=(const const_reverse_iterator& rhv) const;

    protected:
        pointer getPtr() const;

    private:
        explicit const_reverse_iterator(pointer ptr);

    private:
        pointer ptr_;
    };
                                        ///====REVERSE_ITERATOR====
public:
    class reverse_iterator : public const_reverse_iterator {
    friend class Vector<T>;
    public:
        reverse_iterator();
        reverse_iterator(const reverse_iterator& rhv);
        ~reverse_iterator();
        
        reverse_iterator& operator=(const reverse_iterator& rhv);    
        reference         operator*()                             const;
        difference_type   operator-(const reverse_iterator& rhv)  const;
        pointer           operator->()                            const;
        reference         operator[](const size_type index)       const;
        reverse_iterator  operator+(const size_type size)         const;
        reverse_iterator  operator-(const size_type size)         const;
        bool              operator==(const reverse_iterator& rhv) const;
        bool              operator!=(const reverse_iterator& rhv) const;
        bool              operator<(const reverse_iterator& rhv)  const;
        bool              operator>(const reverse_iterator& rhv)  const;
        bool              operator<=(const reverse_iterator& rhv) const;
        bool              operator>=(const reverse_iterator& rhv) const;

    private:
        explicit reverse_iterator(pointer ptr);
    };
                                        ///====VECTOR====  
public:
    Vector();
    Vector(const size_type size, const_reference value = T());
    Vector(const int size, const_reference value = T());
    template <typename InputIterator>
    Vector(InputIterator first, InputIterator last);
    Vector(const Vector<T>& rhv);
    ~Vector();
 
    Vector<T>&      operator=(const Vector<T>& rhv);
    reference       operator[](const size_type index); 
    const_reference operator[](const size_type index) const;
    void*           operator new(const size_type size);
    void            operator delete(void* ptr);
    void*           operator new[](const size_type size);
    void            operator delete[](void* ptr);

    bool            operator==(const Vector<T>& rhv)  const;
    bool            operator!=(const Vector<T>& rhv)  const;
    bool            operator<(const Vector<T>& rhv)   const;
    bool            operator>(const Vector<T>& rhv)   const;
    bool            operator<=(const Vector<T>& rhv)  const;
    bool            operator>=(const Vector<T>& rhv)  const;

    void push_back(const_reference value);
    iterator insert(iterator position, const_reference initialValue);
    void insert(iterator position, size_type count, const_reference initialValue);
    void insert(iterator position, const int count, const_reference initialValue);
    template <typename InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last);

    void pop_back(); 
    iterator erase(iterator posistion);
    iterator erase(iterator first, iterator last);

    void resize(const size_type newSize, const_reference initialValue = T());
    void swap(Vector<T>& rhv);
    void sort();

    size_type capacity()   const;
    size_type size()       const;
    bool      empty()      const;
    void      clear();
    size_type max_size()   const;

    const_iterator begin() const;
    const_iterator end()   const;
    iterator       begin();
    iterator       end();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend()   const;
    reverse_iterator       rbegin();
    reverse_iterator       rend();

    private:
    void shiftToEnd(iterator position, const size_type count);
    void shiftToLeft(iterator position, const size_type count);
    void reserve(const size_type newCapacity);
    template <typename InputIt1, typename InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                 InputIt2 first2, InputIt2 last2);
private:
    T* begin_;
    T* end_;
    T* bufferEnd_;
};

#include "../templates/Vector.cpp"

#endif /// __VECTOR_HPP__

