#include <gtest/gtest.h>
#include "headers/Vector.hpp"
#include <string>
#include <sstream>
#include <vector>

TEST(VectorTest, DefaultConstructor)
{
    Vector<int> v;
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), 0u);
    EXPECT_TRUE(v.empty());
}

TEST(VectorTest, ResizeIncreasesSizeAndCapacity)
{
    Vector<int> v;
    v.resize(5, 42);
    EXPECT_EQ(v.size(), 5u);
    EXPECT_GE(v.capacity(), 5u);
}

TEST(VectorTest, ResizeThenClear)
{
    Vector<int> v;
    v.resize(3, 7);
    EXPECT_FALSE(v.empty());
    v.clear();
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), 0u);
    EXPECT_TRUE(v.empty());
}

TEST(VectorTest, CopyConstructorCopiesSize)
{
    Vector<int> v1;
    v1.resize(4, 10);
    Vector<int> v2(v1);
    EXPECT_EQ(v2.size(), v1.size());
    EXPECT_GE(v2.capacity(), v1.size());
}

TEST(VectorTest, EmptyMethodWorks)
{
    Vector<int> v;
    EXPECT_TRUE(v.empty());
    v.resize(1, 5);
    EXPECT_FALSE(v.empty());
}

TEST(VectorPushBackTest, StoresValuesCorrectly)
{
    Vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.capacity(), 4);
    EXPECT_EQ(v.empty(), false);
}

TEST(VectorPushBackTest, CapacityGrowth)
{
    Vector<int> v;
    double factor = RESERVE_COEFFICIENT;

    v.push_back(1);
    size_t cap1 = v.capacity();

    v.push_back(2);
    size_t cap2 = v.capacity();

    EXPECT_GE(cap2, static_cast<size_t>(cap1 * factor) - 1);
}

TEST(VectorPushBackTest, WorksWithStrings)
{
    Vector<std::string> v;
    v.push_back("hello");
    v.push_back("world");

    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.capacity(), 2);
    EXPECT_EQ(v.empty(), false);
}

TEST(VectorPushBackTest, StoresValuesCorrectly1)
{
    Vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    EXPECT_EQ(v.size(), 3);      
    EXPECT_EQ(v.empty(), false); 

    v.push_back(10);             
}

TEST(VectorPushBackTest, WorksWithStrings1)
{
    Vector<std::string> v;

    v.push_back("hello");
    v.push_back("world");
    v.push_back("!");

    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.empty(), false);
}

TEST(VectorTest, PopBackReducesSize)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);

    size_t oldSize = v.size();
    v.pop_back();

    EXPECT_EQ(v.size(), oldSize - 1);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.capacity() >= v.size(), true);
}

TEST(VectorTest, PopBackRemovesLastElement)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.pop_back();
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.empty(), false);
    EXPECT_EQ(v.capacity() >= v.size(), true);
    EXPECT_EQ(v.size(), 2);
}

TEST(VectorTest, DefaultConstructor1)
{
    Vector<int> v;
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.capacity(), 0u);
}

TEST(VectorIteratorTest, ForwardTraversal)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    Vector<int>::iterator it = v.begin();
    EXPECT_EQ(*it, 1);

    ++it;
    EXPECT_EQ(*it, 2);

    it++;
    EXPECT_EQ(*it, 3);
}

TEST(VectorIteratorTest, BackwardTraversal)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    Vector<int>::iterator it = v.end();
    --it;
    EXPECT_EQ(*it, 30);

    it--;
    EXPECT_EQ(*it, 20);

    --it;
    EXPECT_EQ(*it, 10);
}

TEST(VectorIteratorTest, IndexingOperator)
{
    Vector<int> v(5, 42);
    Vector<int>::iterator it = v.begin();

    EXPECT_EQ(it[0], 42);
    EXPECT_EQ(it[4], 42);
}

TEST(VectorIteratorTest, ArithmeticOperators)
{
    Vector<int> v;
    for (int i = 0; i < 5; ++i) v.push_back(i);

    Vector<int>::iterator it1 = v.begin();
    Vector<int>::iterator it2 = it1 + 3;

    EXPECT_EQ(*it2, 3);

    it2 -= 2;
    EXPECT_EQ(*it2, 1);

    Vector<int>::iterator it3 = it2 - 1;
    EXPECT_EQ(*it3, 0);

    EXPECT_EQ(it2 - it1, 1u);
}

TEST(VectorConstIteratorTest, ForwardTraversal)
{
    Vector<int> v;
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);

    Vector<int>::const_iterator it = v.begin();
    EXPECT_EQ(*it, 5);

    ++it;
    EXPECT_EQ(*it, 6);

    it++;
    EXPECT_EQ(*it, 7);
}

TEST(VectorConstIteratorTest, BackwardTraversal)
{
    Vector<int> v;
    v.push_back(100);
    v.push_back(200);

    Vector<int>::const_iterator it = v.end();
    --it;
    EXPECT_EQ(*it, 200);

    it--;
    EXPECT_EQ(*it, 100);
}

TEST(VectorConstIteratorTest, IndexingOperator)
{
    Vector<int> v(4, 99);
    Vector<int>::const_iterator it = v.begin();

    EXPECT_EQ(it[0], 99);
    EXPECT_EQ(it[3], 99);
}

TEST(VectorConstIteratorTest, ArithmeticOperators)
{
    Vector<int> v;
    for (int i = 0; i < 6; ++i) v.push_back(i * 10);

    Vector<int>::const_iterator it1 = v.begin();
    Vector<int>::const_iterator it2 = it1 + 4;

    EXPECT_EQ(*it2, 40);

    it2 -= 3;
    EXPECT_EQ(*it2, 10);

    Vector<int>::const_iterator it3 = it2 - 1;
    EXPECT_EQ(*it3, 0);

    EXPECT_TRUE(it1 != it2);
    it2 -= 1;
    EXPECT_TRUE(it1 == it2);
}

TEST(VectorReverseIteratorTest, SingleElementDereference)
{
    Vector<int> v(1, 5);
    Vector<int>::reverse_iterator rbegin = v.rbegin();
    EXPECT_EQ(*rbegin, 5);
}

TEST(VectorReverseIteratorTest, MultipleElementsOrder)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    Vector<int>::reverse_iterator it = v.rbegin();
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 1);
}

TEST(VectorReverseIteratorTest, PreIncrementMovesBackward)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    Vector<int>::reverse_iterator it = v.rbegin();
    ++it;
    EXPECT_EQ(*it, 20);
}

TEST(VectorReverseIteratorTest, PreDecrementMovesForward)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    Vector<int>::reverse_iterator it = v.rend();
    --it;
    EXPECT_EQ(*it, 10);
}

TEST(VectorReverseIteratorTest, IndexingOperator)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    Vector<int>::reverse_iterator it = v.rbegin();
    EXPECT_EQ(it[0], 4);
    EXPECT_EQ(it[1], 3);
    EXPECT_EQ(it[2], 2);
    EXPECT_EQ(it[3], 1);
}

TEST(VectorReverseIteratorTest1, SingleElementDereference)
{
    Vector<int> v(1, 5);
    Vector<int>::reverse_iterator rbegin = v.rbegin();
    EXPECT_EQ(*rbegin, 5);
}

TEST(VectorReverseIteratorTest1, MultipleElementsOrder)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    Vector<int>::reverse_iterator it = v.rbegin();
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 1);
}

TEST(VectorReverseIteratorTest1, PreIncrementMovesBackward)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    Vector<int>::reverse_iterator it = v.rbegin();
    ++it;
    EXPECT_EQ(*it, 20);
}

TEST(VectorReverseIteratorTest1, PreDecrementMovesForward)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    Vector<int>::reverse_iterator it = v.rend();
    --it;
    EXPECT_EQ(*it, 10);
}

TEST(VectorReverseIteratorTest1, IndexingOperator)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    Vector<int>::reverse_iterator it = v.rbegin();
    EXPECT_EQ(it[0], 4);
    EXPECT_EQ(it[1], 3);
    EXPECT_EQ(it[2], 2);
    EXPECT_EQ(it[3], 1);
}

TEST(VectorReverseIteratorTest, PointerOperator)
{
    Vector<int> v(1, 42);
    Vector<int>::reverse_iterator it = v.rbegin();
    EXPECT_EQ(*it, 42);
}

TEST(VectorReverseIteratorTest, AdditionOperator)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    Vector<int>::reverse_iterator it = v.rbegin();
    Vector<int>::reverse_iterator it2 = it + 2;
    EXPECT_EQ(*it2, 20);
}

TEST(VectorReverseIteratorTest, SubtractionOperator)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    Vector<int>::reverse_iterator it = v.rend();
    Vector<int>::reverse_iterator it2 = it - 2;
    EXPECT_EQ(*it2, 20);
}

TEST(VectorReverseIteratorTest, PlusEqualsOperator)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    Vector<int>::reverse_iterator it = v.rbegin();
    it += 3;
    EXPECT_EQ(*it, 10);
}

TEST(VectorReverseIteratorTest, MinusEqualsOperator)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    Vector<int>::reverse_iterator it = v.rend();
    it -= 1;
    EXPECT_EQ(*it, 10);
}

TEST(VectorReverseIteratorTest, DistanceBetweenIterators)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    Vector<int>::reverse_iterator it1 = v.rbegin();
    Vector<int>::reverse_iterator it2 = v.rend();
    EXPECT_EQ(it2 - it1, -4);
}

TEST(VectorReverseIteratorTest, IterateWholeVector)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    std::vector<int> result;
    for(Vector<int>::reverse_iterator it=v.rbegin(); it!=v.rend(); ++it) {
        result.push_back(*it);
    }

    std::vector<int> expected;
    expected.push_back(5);
    expected.push_back(4);
    expected.push_back(3);
    expected.push_back(2);
    expected.push_back(1);

    EXPECT_EQ(result, expected);
}

// ================= Const Reverse Iterator tests =================

TEST(VectorConstReverseIteratorTest, SingleElementDereference)
{
    Vector<int> v(1, 9);
    Vector<int>::const_reverse_iterator it = v.rbegin();
    EXPECT_EQ(*it, 9);
}

TEST(VectorConstReverseIteratorTest, MultipleElementsOrder)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    Vector<int>::const_reverse_iterator it = v.rbegin();
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 1);
}

TEST(VectorConstReverseIteratorTest, PreIncrementMovesBackward)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    Vector<int>::const_reverse_iterator it = v.rbegin();
    ++it;
    EXPECT_EQ(*it, 20);
}

TEST(VectorConstReverseIteratorTest, PostIncrementMovesBackward)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    Vector<int>::const_reverse_iterator it = v.rbegin();
    Vector<int>::const_reverse_iterator old = it++;
    EXPECT_EQ(*old, 30);
    EXPECT_EQ(*it, 20);
}

TEST(VectorConstReverseIteratorTest, PreDecrementMovesForward)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    Vector<int>::const_reverse_iterator it = v.rend();
    --it;
    EXPECT_EQ(*it, 10);
}

TEST(VectorConstReverseIteratorTest, EqualityAndInequality)
{
    Vector<int> v(3, 7);
    Vector<int>::const_reverse_iterator it1 = v.rbegin();
    Vector<int>::const_reverse_iterator it2 = v.rbegin();
    Vector<int>::const_reverse_iterator it3 = v.rend();
    EXPECT_TRUE(it1 == it2);
    EXPECT_TRUE(it1 != it3);
}

TEST(VectorConstReverseIteratorTest, IndexingOperator)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    Vector<int>::const_reverse_iterator it = v.rbegin();
    EXPECT_EQ(it[0], 4);
    EXPECT_EQ(it[1], 3);
    EXPECT_EQ(it[2], 2);
    EXPECT_EQ(it[3], 1);
}

TEST(VectorConstReverseIteratorTest, PointerOperator)
{
    Vector<int> v(1, 42);
    Vector<int>::const_reverse_iterator it = v.rbegin();
    EXPECT_EQ(*it, 42);
}

TEST(VectorConstReverseIteratorTest, AdditionOperator)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    Vector<int>::const_reverse_iterator it = v.rbegin();
    Vector<int>::const_reverse_iterator it2 = it + 2;
    EXPECT_EQ(*it2, 20);
}

TEST(VectorConstReverseIteratorTest, SubtractionOperator)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    Vector<int>::const_reverse_iterator it = v.rend();
    Vector<int>::const_reverse_iterator it2 = it - 2;
    EXPECT_EQ(*it2, 20);
}

TEST(VectorConstReverseIteratorTest, PlusEqualsOperator)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    Vector<int>::const_reverse_iterator it = v.rbegin();
    it += 3;
    EXPECT_EQ(*it, 10);
}

TEST(VectorConstReverseIteratorTest, MinusEqualsOperator)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    Vector<int>::const_reverse_iterator it = v.rend();
    it -= 1;
    EXPECT_EQ(*it, 10);
}

TEST(VectorConstReverseIteratorTest, DistanceBetweenIterators)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    Vector<int>::const_reverse_iterator it1 = v.rbegin();
    Vector<int>::const_reverse_iterator it2 = v.rend();

    EXPECT_EQ((it2 - it1), -4);
}

TEST(VectorConstReverseIteratorTest, IterateWholeVector)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    std::vector<int> result;
    for(Vector<int>::const_reverse_iterator it=v.rbegin(); it!=v.rend(); ++it) {
        result.push_back(*it);
    }

    std::vector<int> expected;
    expected.push_back(5);
    expected.push_back(4);
    expected.push_back(3);
    expected.push_back(2);
    expected.push_back(1);

    EXPECT_EQ(result, expected);
}

TEST(VectorReverseIteratorTest2, EqualityAndInequality)
{
    Vector<int> v(3, 7);
    Vector<int>::reverse_iterator it1 = v.rbegin();
    Vector<int>::reverse_iterator it2 = v.rbegin();
    Vector<int>::reverse_iterator it3 = v.rend();
    EXPECT_TRUE(it1 == it2); 
    EXPECT_TRUE(it1 != it3);
}

TEST(VectorConstReverseIteratorTest2, PostDecrementMovesForward)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    Vector<int>::const_reverse_iterator it = v.rend();
    Vector<int>::const_reverse_iterator old = --it;
    EXPECT_TRUE(--old == v.rbegin() + 1); 
}

TEST(VectorConstReverseIteratorTest2, EqualityAndInequality)
{
    Vector<int> v(3, 7);
    Vector<int>::const_reverse_iterator it1 = v.rbegin();
    Vector<int>::const_reverse_iterator it2 = v.rbegin();
    Vector<int>::const_reverse_iterator it3 = v.rend();
    EXPECT_TRUE(it1 == it2); 
    EXPECT_TRUE(it1 != it3);
}

TEST(VectorRangeConstructorTest, FromArray)
{
    int arr[] = {1, 2, 3, 4};
    Vector<int> v(arr, arr + 4);

    EXPECT_EQ(*(v.begin() + 0), 1);
    EXPECT_EQ(*(v.begin() + 1), 2);
    EXPECT_EQ(*(v.begin() + 2), 3);
    EXPECT_EQ(*(v.begin() + 3), 4);
}

TEST(VectorRangeConstructorTest, FromAnotherVector)
{
    Vector<int> base;
    base.push_back(10);
    base.push_back(20);
    base.push_back(30);

    Vector<int> copy(base.begin(), base.end());

    EXPECT_EQ(*(copy.begin() + 0), 10);
    EXPECT_EQ(*(copy.begin() + 1), 20);
    EXPECT_EQ(*(copy.begin() + 2), 30);
}

TEST(VectorRangeConstructorTest, FromEmptyRange)
{
    int* p = 0;
    Vector<int> v(p, p);

    EXPECT_TRUE(v.begin() == v.end());
}

TEST(VectorInsertTest, InsertSingle)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(3);

    v.insert(v.begin() + 1, 2);

    EXPECT_EQ(*(v.begin() + 0), 1);
    EXPECT_EQ(*(v.begin() + 1), 2);
    EXPECT_EQ(*(v.begin() + 2), 3);
}

TEST(VectorInsertTest, InsertMultipleCount)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(5);

    v.insert(v.begin() + 1, 3, 2);

    EXPECT_EQ(*(v.begin() + 0), 1);
    EXPECT_EQ(*(v.begin() + 1), 2);
    EXPECT_EQ(*(v.begin() + 2), 2);
    EXPECT_EQ(*(v.begin() + 3), 2);
    EXPECT_EQ(*(v.begin() + 4), 5);
}

TEST(VectorInsertTest, InsertRangeFromVector)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(5);

    Vector<int> other;
    other.push_back(2);
    other.push_back(3);
    other.push_back(4);

    v.insert(v.begin() + 1, other.begin(), other.end());

    EXPECT_EQ(*(v.begin() + 0), 1);
    EXPECT_EQ(*(v.begin() + 1), 2);
    EXPECT_EQ(*(v.begin() + 2), 3);
    EXPECT_EQ(*(v.begin() + 3), 4);
    EXPECT_EQ(*(v.begin() + 4), 5);
}

TEST(VectorEraseTest, EraseSingle)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    Vector<int>::iterator it = v.erase(v.begin() + 1); 

    EXPECT_EQ(*(v.begin() + 0), 10);
    EXPECT_EQ(*(v.begin() + 1), 30);
    EXPECT_EQ(*it, 30);
}

TEST(VectorEraseTest, EraseRange)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    Vector<int>::iterator it = v.erase(v.begin() + 1, v.begin() + 4);

    EXPECT_EQ(*(v.begin() + 0), 1);
    EXPECT_EQ(*(v.begin() + 1), 5);
    EXPECT_EQ(*it, 5);
}
/// ====
TEST(VectorOperatorsTest, AssignmentAndEquality)
{
    std::vector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    std::vector<int> b;
    b.push_back(1);
    b.push_back(2);
    b.push_back(3);

    std::vector<int> d;
    d = a; 

    EXPECT_TRUE(d == a); 
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(VectorOperatorsTest, InequalityComparisons)
{
    std::vector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    std::vector<int> c;
    c.push_back(1);
    c.push_back(2);
    c.push_back(4);

    EXPECT_TRUE(a < c); 
    EXPECT_FALSE(c < a);

    EXPECT_FALSE(a > c);
    EXPECT_TRUE(c > a);

    EXPECT_TRUE(a <= c);
    EXPECT_TRUE(a <= a);
    EXPECT_TRUE(c >= a);
    EXPECT_TRUE(a >= a);
}

TEST(VectorTest, Swap)
{
    std::vector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    std::vector<int> b;
    b.push_back(9);
    b.push_back(8);

    EXPECT_EQ(a.size(), 3u);
    EXPECT_EQ(b.size(), 2u);

    a.swap(b);

    EXPECT_EQ(a.size(), 2u);
    EXPECT_EQ(b.size(), 3u);

    EXPECT_EQ(a[0], 9);
    EXPECT_EQ(a[1], 8);

    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b[2], 3);
}

TEST(VectorOperatorsTest, MaxSize)
{
    std::vector<int> a;
    EXPECT_GT(a.max_size(), 0u);
}

TEST(VectorSortTest, SortAscending)
{
    Vector<int> v;
    v.push_back(10);
    v.push_back(3);
    v.push_back(7);
    v.push_back(1);
    v.push_back(5);

    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[4], 5);

    v.sort();

    EXPECT_EQ(v.size(), 5u);

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 5);
    EXPECT_EQ(v[3], 7);
    EXPECT_EQ(v[4], 10);
}

TEST(VectorSortTest, AlreadySorted)
{
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    v.sort();

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
}

TEST(VectorOperatorNewDelete, SingleObject)
{
    Vector<int>* v = new Vector<int>();
    EXPECT_NE(v, (Vector<int>*)0); 

    delete v; 
}

TEST(VectorOperatorNewDelete, ArrayOfObjects)
{
    Vector<int>* arr = new Vector<int>[5];
    EXPECT_NE(arr, (Vector<int>*)0);

    delete[] arr;
}

TEST(VectorStreamOperators, OutputOperator)
{
    Vector<int> v(3, 5);
    std::stringstream ss;
    ss << v;

    EXPECT_EQ(ss.str(), "{ 5 5 5 }");
}

TEST(VectorStreamOperators, InputOperator)
{
    Vector<int> v(3, 0);
    std::stringstream ss("1 2 3");
    ss >> v;

    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorResize, ShrinkStrings)
{
    Vector<std::string> v;
    v.push_back("one");
    v.push_back("two");
    v.push_back("three");

    v.resize(2); 

    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0], "one");
    EXPECT_EQ(v[1], "two");
}

TEST(VectorResize, ExpandWithDefaultStrings)
{
    Vector<std::string> v;
    v.push_back("a");
    v.push_back("b");

    v.resize(4); 

    EXPECT_EQ(v.size(), 4u);
    EXPECT_EQ(v[0], "a");
    EXPECT_EQ(v[1], "b");
    EXPECT_EQ(v[2], ""); 
    EXPECT_EQ(v[3], "");
}

TEST(VectorResize, ExpandWithCustomValue)
{
    Vector<std::string> v;
    v.push_back("hello");

    v.resize(3, "X");

    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], "hello");
    EXPECT_EQ(v[1], "X");
    EXPECT_EQ(v[2], "X");
}

TEST(VectorResize, ResizeNoChange)
{
    Vector<std::string> v;
    v.push_back("alpha");
    v.push_back("beta");

    v.resize(2);

    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0], "alpha");
    EXPECT_EQ(v[1], "beta");
}

struct A {
    A() {std::cout << "A::A\n";}
    int a;
    int b;
};

TEST(VectorResize, ResizeNoChange1)
{
    Vector<A> v(5);
}


int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

