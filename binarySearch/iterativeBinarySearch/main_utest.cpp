#include "headers/function.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <set>

TEST(BinarySearchTest, VectorFound)
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    std::vector<int>::iterator it = binarySearch(v.begin(), v.end(), 3);
    EXPECT_NE(it, v.end());
    EXPECT_EQ(*it, 3);
}

TEST(BinarySearchTest, VectorNotFound)
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    std::vector<int>::iterator it = binarySearch(v.begin(), v.end(), 10);
    EXPECT_EQ(it, v.end());
}

TEST(BinarySearchTest, ListFound)
{
    std::list<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    std::list<int>::iterator it = binarySearch(l.begin(), l.end(), 20);
    EXPECT_NE(it, l.end());
    EXPECT_EQ(*it, 20);
}

TEST(BinarySearchTest, ListNotFound)
{
    std::list<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    std::list<int>::iterator it = binarySearch(l.begin(), l.end(), 40);
    EXPECT_EQ(it, l.end());
}

TEST(BinarySearchTest, SetFound)
{
    std::set<int> s;
    s.insert(7);
    s.insert(14);
    s.insert(21);
    std::set<int>::iterator it = binarySearch(s.begin(), s.end(), 14);
    EXPECT_NE(it, s.end());
    EXPECT_EQ(*it, 14);
}

TEST(BinarySearchTest, SetNotFound)
{
    std::set<int> s;
    s.insert(7);
    s.insert(14);
    s.insert(21);
    std::set<int>::iterator it = binarySearch(s.begin(), s.end(), 99);
    EXPECT_EQ(it, s.end());
}

int
main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

