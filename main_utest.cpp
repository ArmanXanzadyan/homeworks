#include "headers/Map.hpp"
#include <gtest/gtest.h>
#include <sstream>
#include <utility>

TEST(a, b)
{
    typedef Map<int, int>::iterator MIt;
    Map<int, int> s;
    s.insert(std::make_pair(-1, 1));
    s.insert(std::make_pair(-2, 2));
    s.insert(std::make_pair(-3, 3));
    
    MIt it = s.begin();
    std::cout << (*it).first << ": " << (*it).second << std::endl;
    std::cout << it->first << ": " << it->second << std::endl;
    ++it; 
    std::cout << (*it).first << ": " << (*it).second << std::endl;
    std::cout << it->first << ": " << it->second << std::endl;
    ++it; 
    std::cout << (*it).first << ": " << (*it).second << std::endl;
    std::cout << it->first << ": " << it->second << std::endl;
    ++it; 
    std::cout << std::boolalpha;
    std::cout << (it == s.end()) << std::endl;
    std::stringstream ss;
    s.print(ss);
    EXPECT_EQ(ss.str(), "{ -3:3 -2:2 -1:1 }");
}
  
TEST(Mapint, insert)
{
    Map<int, int> s;
    s.insert(std::make_pair(1, 100));
    s.insert(std::make_pair(2, 50));
    s.insert(std::make_pair(3, 150));
    s.insert(std::make_pair(4, 20));
    s.insert(std::make_pair(5, 70));
    s.insert(std::make_pair(6, 120));
    s.insert(std::make_pair(7, 170));
    s.insert(std::make_pair(8, 10));
    s.insert(std::make_pair(9, 30));
    s.insert(std::make_pair(10, 60));
    s.insert(std::make_pair(11, 80));
    s.insert(std::make_pair(12, 110));
    s.insert(std::make_pair(13, 130));
    s.insert(std::make_pair(14, 160));
    s.insert(std::make_pair(15, 180));
    
    std::stringstream ss;
    s.print(ss);
    EXPECT_EQ(ss.str(), "{ 1:100 2:50 3:150 4:20 5:70 6:120 7:170 8:10 9:30 10:60 11:80 12:110 13:130 14:160 15:180 }"); 
    
    std::cout << s << std::endl;
    s.erase(s.begin());
    std::cout << s << "\n\n" << std::endl;
     
    s.erase(s.begin());
    std::cout << s << "\n\n" << std::endl;
    s.erase(s.begin());
    std::cout << s << "\n\n" << std::endl;
    s.erase(s.begin());
    std::cout << s << "\n\n" << std::endl;
    s.erase(s.begin());
    std::cout << s << "\n\n" << std::endl;
    s.erase(s.begin());
    std::cout << s << "\n\n" << std::endl;
    s.erase(s.begin());
    std::cout << s << "\n\n" << std::endl;
    s.erase(s.begin());
    std::cout << s << "\n\n" << std::endl;
    s.erase(s.begin());
    std::cout << s << "\n\n" << std::endl;
    s.erase(s.begin());
    std::cout << s << "\n\n" << std::endl;
    s.erase(s.begin());
    std::cout << s << "\n\n" << std::endl;
    s.erase(s.begin());
    std::cout << s << "\n\n" << std::endl;
    s.erase(s.begin());
    std::cout << s << "\n\n" << std::endl;
    s.erase(s.begin());
    std::cout << s << "\n\n" << std::endl;
    s.erase(s.begin());
    std::cout << s << "\n\n" << std::endl;
    EXPECT_TRUE(s.empty());
    
    const int size = 9;
    std::pair<int, int> arr[size] = {
       std::make_pair(11, 11), 
       std::make_pair(22, 22), 
       std::make_pair(33, 33), 
       std::make_pair(44, 44), 
       std::make_pair(55, 55), 
       std::make_pair(66, 66), 
       std::make_pair(77, 77), 
       std::make_pair(88, 88), 
       std::make_pair(99, 99)
    }; 
    s.insert(arr, arr + size);
    std::cout << s << std::endl;
}

TEST(MapInt, CopyConstructor)
{
    Map<int, int> s;
    s.insert(std::make_pair(1, 1));
    s.insert(std::make_pair(1, 2));
    s.insert(std::make_pair(1, 3));
    s.insert(std::make_pair(1, 4));
    
    Map<int, int> b = s;
    EXPECT_TRUE(b == s);
    
    Map<int, int> c;
    c = b;
    EXPECT_TRUE(c == s);

    std::stringstream ss1;
    c.print(ss1);
    std::stringstream ss2;
    s.print(ss2);
    EXPECT_EQ(ss1.str(), ss2.str()); 
}

TEST(MapInt, RangeConstructor)
{
    const int size = 6;
    std::pair<int, int> arr[size] = {
       std::make_pair(4, 4), 
       std::make_pair(1, 1),
       std::make_pair(1, 1),
       std::make_pair(4, 4),
       std::make_pair(5, 5),
       std::make_pair(6, 6),
    }; 
    Map<int, int> s(arr, arr + size);
    std::stringstream ss;
    s.print(ss);
    EXPECT_EQ(ss.str(), "{ 1:1 4:4 5:5 6:6 }");

}

TEST(MapInt, EraseIterator1)
{
    Map<int, int> s;
    s.insert(std::make_pair(4, 4));
    s.insert(std::make_pair(1, 1));
    s.insert(std::make_pair(6, 6));
    s.erase(s.begin());
    std::cout << s << std::endl;
    std::stringstream ss;
    s.print(ss);
    EXPECT_EQ(ss.str(), "{ 4:4 6:6 }");
}

TEST(MapInt, EraseIterator2)
{
    Map<int, int> s;
    s.insert(std::make_pair(4, 4));
    s.insert(std::make_pair(1, 1));
    s.insert(std::make_pair(6, 6));
    s.erase(++s.begin());
    std::cout << s << std::endl;
    std::stringstream ss;
    s.print(ss);
    EXPECT_EQ(ss.str(), "{ 1:1 6:6 }");
}

TEST(MapInt, EraseIterator3)
{
    Map<int, int> s;
    s.insert(std::make_pair(4, 4));
    std::cout << s << std::endl;
    s.insert(std::make_pair(1, 1));
    std::cout << s << std::endl;
    s.insert(std::make_pair(3, 3));
    std::cout << s << std::endl;
    s.erase(++(++s.begin()));
    std::cout << s << std::endl;
    s.erase(++s.begin());
    std::cout << s << std::endl;
    s.erase(s.begin());
    std::cout << s << std::endl;
    std::stringstream ss;
    s.print(ss);
    EXPECT_TRUE(s.empty());
}

TEST(MapInt, RangeErase)
{
    Map<int, int> s;
    s.insert(std::make_pair(3, 3));
    s.insert(std::make_pair(2, 2));
    s.insert(std::make_pair(1, 1));
    
    std::cout << s << std::endl;
    
    s.erase(++(s.begin()));
    std::cout << s << "\n\n" << std::endl;
    
    s.erase(s.begin());
    std::cout << s << "\n\n" << std::endl;
    
    s.erase(s.begin());
    std::cout << s << "\n\n" << std::endl;
    EXPECT_TRUE(s.empty());
    s.clear(); 

    Map<int, int>::iterator it = s.begin();
    Map<int, int>::iterator jt = s.end();
    s.erase(it, jt);
    s.print();
}

TEST(MapInt, Big_RangeErase)
{
    Map<int, int> s;
    s.insert(std::make_pair(4, 4));
    s.insert(std::make_pair(1, 1));
    s.insert(std::make_pair(6, 6));
    s.insert(std::make_pair(32, 32));
    s.insert(std::make_pair(13, 13));
    s.insert(std::make_pair(10, 10));
    s.insert(std::make_pair(11, 11));
    s.insert(std::make_pair(30, 30));
    std::cout << s << std::endl;
    Map<int, int>::iterator it = s.begin();
    Map<int, int>::iterator jt = s.end();
    s.erase(it, jt);
    s.print();
    EXPECT_TRUE(s.empty());
}

TEST(MapInt, RangeErase1)
{
    std::pair<int, int> arr[] = {
       std::make_pair(4, 4), 
       std::make_pair(1, 1),
       std::make_pair(9, 9),
       std::make_pair(2, 2),
       std::make_pair(7, 7),
       std::make_pair(6, 6),
    }; 
    Map<int, int> s(arr, arr + 6);
    Map<int, int>::iterator it = s.begin();
    Map<int, int>::iterator jt = s.end();
    EXPECT_EQ(it->first, 1);
    std::cout << s << std::endl;
    s.erase(it, jt);
    EXPECT_TRUE(s.empty());
}

TEST(MapInt, eraseKey)
{
    std::pair<int, int> arr[] = {
       std::make_pair(4, 4), 
       std::make_pair(1, 1),
       std::make_pair(9, 9),
       std::make_pair(2, 2),
       std::make_pair(7, 7),
       std::make_pair(6, 6),
    }; 
    Map<int, int> s(arr, arr + 6);
    std::cout << s << std::endl;
    s.erase(1);
    std::cout << s << std::endl;
    s.erase(4);
    std::cout << s << std::endl;
    s.erase(9);
    std::cout << s << std::endl;
    s.erase(2);
    std::cout << s << std::endl;
    s.erase(7);
    std::cout << s << std::endl;
    s.erase(6);
    std::cout << s << std::endl;
    EXPECT_TRUE(s.empty());
}

TEST(MapInt, erase42)
{
    Map<int, int> s;
    s.insert(std::make_pair(3, 3));
    s.insert(std::make_pair(2, 2));
    s.insert(std::make_pair(15, 15));
    s.insert(std::make_pair(12, 12));
    s.insert(std::make_pair(18, 18));
    s.insert(std::make_pair(0, 0));
    s.insert(std::make_pair(11, 11));
    s.insert(std::make_pair(13, 13));
    s.insert(std::make_pair(16, 16));
    s.insert(std::make_pair(19, 19));
    std::cout << s << "\n\n" << std::endl;
    
}

TEST(MapInt, decrement)
{
    Map<int, int> s;
    s.insert(std::make_pair(3, 3));
    s.insert(std::make_pair(2, 2));
    s.insert(std::make_pair(15, 15));
    s.insert(std::make_pair(12, 12));
    s.insert(std::make_pair(18, 18));
    s.insert(std::make_pair(0, 0));
    s.insert(std::make_pair(11, 11));
    s.insert(std::make_pair(13, 13));
    s.insert(std::make_pair(16, 16));
    s.insert(std::make_pair(19, 19));
    std::cout << s << "\n\n" << std::endl;
    Map<int, int>::const_iterator first = s.begin();
    while (first != s.end()) {
        std::cout << first->first << ":" << first->second << ' ';
        ++first;
    } 
    std::cout << std::endl;
    Map<int, int>::const_iterator last = s.find(19); 
    while (last != s.end()) {
        std::cout << last->first << ":" << last->second << ' ';
        --last;
    } 
    std::cout << std::endl;
    Map<int, int>::reverse_iterator b = s.rbegin();
    while (b != s.rend()) { std::cout << (*b).first << (*b) .second << ' '; ++b; }
    b = s.rbegin();
    std::cout << (*(b.operator->())).first << ":" << (*(b.operator->())).second << std::endl;    
}

TEST(MapInt, bounds)
{
    Map<int, int> s;
    s.insert(std::make_pair(3, 3));
    s.insert(std::make_pair(2, 2));
    s.insert(std::make_pair(15, 15));
    s.insert(std::make_pair(12, 12));
    s.insert(std::make_pair(18, 18));
    s.insert(std::make_pair(0, 0));
    s.insert(std::make_pair(11, 11));
    s.insert(std::make_pair(13, 13));
    s.insert(std::make_pair(16, 16));
    s.insert(std::make_pair(19, 19));
    std::cout << s << "\n\n" << std::endl;
    int key1 = 4;
    EXPECT_TRUE(s.lower_bound(key1)->first == 11);
    EXPECT_TRUE(s.upper_bound(key1)->first == 11);
    int key2 = 16;
    EXPECT_TRUE(s.lower_bound(key2)->first == 16);
    EXPECT_TRUE(s.upper_bound(key2)->first == 18);
}

TEST(MapInt, eraseKey4)
{
    Map<int, int> s;
    s.insert(std::make_pair(10, 10));
    s.insert(std::make_pair(5, 5));
    s.insert(std::make_pair(15, 15));
    s.insert(std::make_pair(2, 2));
    s.insert(std::make_pair(8, 8));
    s.insert(std::make_pair(12, 12));
    s.insert(std::make_pair(18, 18));
    s.insert(std::make_pair(0, 0));
    s.insert(std::make_pair(3, 3));
    s.insert(std::make_pair(6, 6));
    s.insert(std::make_pair(9, 9));
    s.insert(std::make_pair(11, 11));
    s.insert(std::make_pair(13, 13));
    s.insert(std::make_pair(16, 16));
    s.insert(std::make_pair(19, 19));
    std::cout << s << "\n\n" << std::endl;
    
    s.erase(5);
    std::cout << s << "\n\n" << std::endl;
    
    s.erase(10);
    std::cout << s << "\n\n" << std::endl;
    s.erase(9);
    std::cout << s << "\n\n" << std::endl;
    s.erase(8);
    std::cout << s << "\n\n" << std::endl;
    s.erase(6);
    std::cout << s << "\n\n" << std::endl;
    s.erase(3);
    std::cout << s << "\n\n" << std::endl;
    s.erase(0);
    std::cout << s << "\n\n" << std::endl;
    s.erase(2);
    std::cout << s << "\n\n" << std::endl;
    
    std::stringstream ss1, ss2;
    s.preOrderIter(ss1);
    s.preOrderRec(ss2);
    EXPECT_TRUE(ss1.str() == ss2.str()); 
    
    ss1.str("");
    ss2.str("");
    s.inOrderIter(ss1);
    s.inOrderRec(ss2);
    s.inOrderIter();
    s.inOrderRec();
    EXPECT_TRUE(ss1.str() == ss2.str()); 
    
    ss1.str("");
    ss2.str("");
    s.postOrderRec(ss2);
    EXPECT_EQ(ss2.str(), "11:11 13:13 12:12 16:16 19:19 18:18 15:15 ");
    s.postOrderIter(ss1);
    EXPECT_EQ(ss1.str(), "11:11 13:13 12:12 16:16 19:19 18:18 15:15 ");
}

TEST(MapInt, eraseKey5)
{
    Map<int, int> s;
    s.insert(std::make_pair(10, 10));
    s.insert(std::make_pair(5, 5));
    s.insert(std::make_pair(15, 15));
    s.insert(std::make_pair(2, 2)).first;
    s.insert(std::make_pair(8, 8));
    s.insert(std::make_pair(12, 12));
    s.insert(std::make_pair(18, 18));
    s.insert(std::make_pair(0, 0));
    s.insert(std::make_pair(3, 3));
    s.insert(std::make_pair(6, 6));
    s.insert(std::make_pair(9, 9));
    s.insert(std::make_pair(11, 11));
    s.insert(std::make_pair(13, 13));
    s.insert(std::make_pair(16, 16));
    s.insert(std::make_pair(19, 19));
    s.insert(std::make_pair(20, 20));
    std::cout << s << "\n\n" << std::endl;
    
    EXPECT_TRUE(int() == s[33]); 
    std::cout << s[33] << std::endl;
    std::cout << s[33] << std::endl;
    s[33] = 77;
    s[11] = 77;
    std::cout << s[33] << std::endl;
    std::cout << s << "\n\n" << std::endl;
    std::pair<Map<int, int>::iterator, bool> pt = s.insert(std::make_pair(9, 8));
    std::cout << std::boolalpha;
    std::cout << *pt.first << ":" << pt.second << std::endl;
    std::cout << s << "\n\n" << std::endl;
}

TEST(MapInt, bound)
{
    Map<int, int> s;
    s.insert(std::make_pair(10, 10));
    s.insert(std::make_pair(5, 5));
    s.insert(std::make_pair(15, 15));
    s.insert(std::make_pair(2, 2)).first;
    s.insert(std::make_pair(8, 8));
    s.insert(std::make_pair(12, 12));
    s.insert(std::make_pair(18, 18));
    s.insert(std::make_pair(0, 0));
    s.insert(std::make_pair(3, 3));
    s.insert(std::make_pair(6, 6));
    s.insert(std::make_pair(9, 9));
    s.insert(std::make_pair(11, 11));
    s.insert(std::make_pair(13, 13));
    s.insert(std::make_pair(16, 16));
    s.insert(std::make_pair(19, 19));
    std::cout << s << "\n\n" << std::endl;
    
    std::cout << *s.find(11) << std::endl;
    std::cout << *s.lower_bound(11) << std::endl;
    std::cout << std::boolalpha << (s.find(11) == s.lower_bound(11)) << std::endl;
    EXPECT_TRUE(s.lower_bound(11) == s.find(11));
    EXPECT_TRUE(s.upper_bound(11) == s.find(12));
    EXPECT_TRUE(s.equal_range(11).first == s.lower_bound(11));
    EXPECT_TRUE(s.equal_range(11).second == s.upper_bound(11));
}

TEST(SetInt, bound)
{
    Map<double, double> s;
    s.insert(std::make_pair(10, 10));
    s.insert(std::make_pair(5, 5));
    s.insert(std::make_pair(15, 15));
    s.insert(std::make_pair(2, 2));
    s.insert(std::make_pair(8, 8));
    s.insert(std::make_pair(12, 12));
    s.insert(std::make_pair(18, 18));
    s.insert(std::make_pair(0, 0));
    s.insert(std::make_pair(3, 3));
    s.insert(std::make_pair(6, 6));
    s.insert(std::make_pair(9, 9));
    s.insert(std::make_pair(11, 11));
    s.insert(std::make_pair(13, 13));
    s.insert(std::make_pair(16, 16));
    s.insert(std::make_pair(19, 19));
    std::cout << s << "\n\n" << std::endl;
    EXPECT_TRUE(s.lower_bound(15) == s.find(15));
    EXPECT_TRUE(s.upper_bound(15) == s.find(16));
    EXPECT_TRUE(s.lower_bound(17) == s.find(18));
    EXPECT_TRUE(s.upper_bound(17) == s.find(18));
    EXPECT_TRUE(s.lower_bound(4.5) == s.find(5));
    EXPECT_TRUE(s.upper_bound(4.5) == s.find(5));
    EXPECT_TRUE(s.lower_bound(99) == s.end());
    EXPECT_TRUE(s.lower_bound(99) == s.end());
    EXPECT_TRUE(s.upper_bound(99) == s.end());
    EXPECT_TRUE(s.lower_bound(-1) == s.begin());
    EXPECT_TRUE(s.upper_bound(-1) == s.begin());
    EXPECT_TRUE(s.equal_range(9).first == s.lower_bound(9));
    EXPECT_TRUE(s.equal_range(9).second == s.upper_bound(9));
    EXPECT_TRUE(++s.equal_range(9).first == s.equal_range(9).second);
}

int
main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}



