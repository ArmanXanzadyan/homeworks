#include "gtest/gtest.h"
#include "headers/String.hpp"
#include <cstring>

TEST(StringTest, DefaultConstructor)
{
    String s;
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_EQ(s.length(), 0u);
    EXPECT_FALSE(s.isDynamic());
    EXPECT_EQ(s.capacity(), 23);
}

TEST(StringTest, StaticConstructor)
{
    String s("Hi");
    EXPECT_STREQ(s.c_str(), "Hi");
    EXPECT_EQ(s.length(), 2u);
    EXPECT_FALSE(s.isDynamic());
    EXPECT_EQ(s.capacity(), SSO_BUFFER_SIZE - 1);
}

TEST(StringTest, DynamicConstructor)
{
    const char* longStr = "This string is definitely longer than SSO_BUFFER_SIZE";
    String s(longStr);
    EXPECT_STREQ(s.c_str(), longStr);
    EXPECT_TRUE(s.isDynamic());
    EXPECT_EQ(s.length(), 53);
    EXPECT_EQ(s.capacity(), s.length());
    EXPECT_EQ(s.length(), std::strlen(longStr));
}

TEST(StringTest, CopyConstructor)
{
    String s1("Hello");
    String s2(s1);

    EXPECT_STREQ(s2.c_str(), "Hello");
    EXPECT_EQ(s2.length(), 5u);
    EXPECT_FALSE(s2.isDynamic());
}

TEST(StringTest, AssignmentOperator)
{
    String s1("Hi");
    String s2;
    s2 = s1;

    EXPECT_STREQ(s2.c_str(), "Hi");
    EXPECT_EQ(s2.length(), 2u);
    EXPECT_FALSE(s2.isDynamic());

    String s3;
    s3 = "This is a long string exceeding SSO_BUFFER_SIZE";
    EXPECT_TRUE(s3.isDynamic());
    EXPECT_EQ(s3.length(), std::strlen("This is a long string exceeding SSO_BUFFER_SIZE"));
}

TEST(StringTest, CStrAndLength)
{
    String s("Hello world");
    EXPECT_STREQ(s.c_str(), "Hello world");
    EXPECT_EQ(s.length(), 11u);
}

TEST(StringTest, StaticVsDynamic)
{
    String staticStr("short");
    String dynamicStr("This string exceeds the small buffer limit");

    EXPECT_FALSE(staticStr.isDynamic());
    EXPECT_TRUE(dynamicStr.isDynamic());
}

TEST(StringTest, MoveConstructorStatic)
{
    String s1("Hi");
    String s2(std::move(s1));

    EXPECT_STREQ(s2.c_str(), "Hi");
    EXPECT_EQ(s2.length(), 2u);
    EXPECT_FALSE(s2.isDynamic());

    EXPECT_EQ(s1.length(), 0u);
    EXPECT_STREQ(s1.c_str(), "");
    EXPECT_FALSE(s1.isDynamic());
}


TEST(StringTest, MoveConstructorDynamic)
{
    String s1("This is a long string exceeding SSO_BUFFER_SIZE");
    bool wasDynamic = s1.isDynamic();

    String s2(std::move(s1));

    EXPECT_TRUE(s2.isDynamic());
    EXPECT_TRUE(wasDynamic);
    EXPECT_STREQ(s2.c_str(), "This is a long string exceeding SSO_BUFFER_SIZE");

    EXPECT_EQ(s1.length(), 0u);
    EXPECT_STREQ(s1.c_str(), "");
    EXPECT_FALSE(s1.isDynamic());
}

TEST(StringTest, MoveAssignmentStatic)
{
    String s1("Hi");
    String s2;
    s2 = std::move(s1);

    EXPECT_STREQ(s2.c_str(), "Hi");
    EXPECT_EQ(s2.length(), 2u);
    EXPECT_FALSE(s2.isDynamic());

    EXPECT_EQ(s1.length(), 0u);
    EXPECT_STREQ(s1.c_str(), "");
    EXPECT_FALSE(s1.isDynamic());
}

TEST(StringTest, MoveAssignmentDynamic)
{
    String s1("This is a long string exceeding SSO_BUFFER_SIZE");
    bool wasDynamic = s1.isDynamic();

    String s2;
    s2 = std::move(s1);

    EXPECT_TRUE(s2.isDynamic());
    EXPECT_TRUE(wasDynamic);
    EXPECT_STREQ(s2.c_str(), "This is a long string exceeding SSO_BUFFER_SIZE");

    EXPECT_EQ(s1.length(), 0u);
    EXPECT_STREQ(s1.c_str(), "");
    EXPECT_FALSE(s1.isDynamic());
}

TEST(StringTest, EqualityOperatorSameStatic)
{
    String a("Hello");
    String b("Hello");

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StringTest, EqualityOperatorDifferentStatic)
{
    String a("Hello");
    String b("World");

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringTest, EqualityOperatorStaticVsDynamicSameContent)
{
    String a("short");
    String b("short");

    b = "This is intentionally long to make it dynamic";
    b = "short";

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StringTest, EqualityOperatorDynamicSame)
{
    String a("This is a long long long long long string");
    String b("This is a long long long long long string");

    EXPECT_TRUE(a.isDynamic());
    EXPECT_TRUE(b.isDynamic());
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StringTest, EqualityOperatorDynamicDifferent)
{
    String a("This is a long long long long long string 111");
    String b("This is a long long long long long string 222");

    EXPECT_TRUE(a.isDynamic());
    EXPECT_TRUE(b.isDynamic());
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringTest, EqualityEmptyStrings)
{
    String a;
    String b;

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(StringTest, EqualityMovedFrom)
{
    String a("Hello");
    String b(std::move(a));

    EXPECT_TRUE(b == String("Hello"));
    EXPECT_FALSE(b != String("Hello"));

    EXPECT_TRUE(a == String(""));
    EXPECT_FALSE(a != String(""));

    EXPECT_EQ(a.length(), 0u);
}

TEST(StringTest, EqualityDifferentLengths)
{
    String a("abc");
    String b("abcd");

    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(StringTest, SubscriptStatic)
{
    String s("Hello");

    EXPECT_EQ(s[0], 'H');
    EXPECT_EQ(s[1], 'e');
    EXPECT_EQ(s[4], 'o');

    s[0] = 'h';
    s[4] = 'O';
    EXPECT_STREQ(s.c_str(), "hellO");
}

TEST(StringTest, SubscriptDynamic)
{
    String s("This is a long string exceeding SSO_BUFFER_SIZE");

    EXPECT_EQ(s[0], 'T');
    EXPECT_EQ(s[5], 'i');
    EXPECT_EQ(s[s.length() - 1], 'E');

    s[0] = 't';
    s[s.length() - 1] = 'e';
    EXPECT_EQ(s[0], 't');
    EXPECT_EQ(s[s.length() - 1], 'e');
}

TEST(StringTest, SubscriptConstAccess)
{
    const String s("Hello");
    EXPECT_EQ(s[1], 'e');
    EXPECT_EQ(s[4], 'o');
}


TEST(StringTest, EmptyTest)
{
    String a;
    EXPECT_TRUE(a.empty());
    EXPECT_EQ(a.length(), 0u);
    EXPECT_STREQ(a.c_str(), "");

    String b("");
    EXPECT_TRUE(b.empty());
    EXPECT_EQ(b.length(), 0u);

    String c("a");
    EXPECT_FALSE(c.empty());
    EXPECT_EQ(c.length(), 1u);

    String d("This is a very very long string");
    EXPECT_FALSE(d.empty());

    d.assign("");
    EXPECT_TRUE(d.empty());
    EXPECT_EQ(d.length(), 0u);

    String e("test");
    String f(std::move(e));
    EXPECT_FALSE(f.empty());
    EXPECT_TRUE(e.empty());
}

TEST(StringTest, AtFunctionStatic)
{
    String s("Hello");

    EXPECT_EQ(s.at(0), 'H');
    EXPECT_EQ(s.at(1), 'e');
    EXPECT_EQ(s.at(4), 'o');

    s.at(0) = 'h';
    s.at(4) = 'O';
    EXPECT_STREQ(s.c_str(), "hellO");
}

TEST(StringPushBackTest, PushBackSSO)
{
    String s("Hi");

    s.push_back('!');
    EXPECT_STREQ(s.c_str(), "Hi!");
    EXPECT_EQ(s.length(), 3u);
    EXPECT_FALSE(s.isDynamic());

    s.push_back('A');
    EXPECT_STREQ(s.c_str(), "Hi!A");
    EXPECT_EQ(s.length(), 4u);
}

TEST(StringPushBackTest, PushBackDynamicGrowth)
{
    const char* longStr = "This string is long enough to be dynamic already";
    String s(longStr);
    EXPECT_TRUE(s.isDynamic());
    size_t oldLen = s.length();

    s.push_back('!');
    EXPECT_TRUE(s.isDynamic());
    EXPECT_EQ(s.length(), oldLen + 1);
    EXPECT_EQ(s.c_str()[oldLen], '!');
    EXPECT_EQ(s.c_str()[s.length()], '\0');

    s.push_back('?');
    EXPECT_EQ(s.c_str()[oldLen + 1], '?');
    EXPECT_EQ(s.c_str()[s.length()], '\0');
}


TEST(StringPushBackTest, PushBackToDynamic)
{
    char buf[SSO_BUFFER_SIZE - 1];
    for (size_t i = 0; i < SSO_BUFFER_SIZE - 2; ++i) buf[i] = 'x';
    buf[SSO_BUFFER_SIZE - 2] = '\0';

    String s(buf);
    EXPECT_FALSE(s.isDynamic());
    EXPECT_EQ(s.length(), SSO_BUFFER_SIZE - 2);

    s.push_back('A');
    EXPECT_TRUE(s.isDynamic());
    EXPECT_EQ(s.length(), SSO_BUFFER_SIZE - 1);
    EXPECT_EQ(s.c_str()[SSO_BUFFER_SIZE - 2], 'A');
    EXPECT_EQ(s.c_str()[s.length()], '\0');
}


TEST(StringPushBackTest, PushBackEmpty)
{
    String s;
    EXPECT_TRUE(s.empty());

    s.push_back('A');
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.length(), 1u);
    EXPECT_STREQ(s.c_str(), "A");
    EXPECT_EQ(s.c_str()[1], '\0');
}

TEST(StringTest, ClearStatic)
{
    String s("Hello");
    EXPECT_FALSE(s.isDynamic());
    EXPECT_EQ(s.length(), 5u);

    s.clear();

    EXPECT_EQ(s.length(), 0u);
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_FALSE(s.isDynamic());
    EXPECT_TRUE(s.empty());
}

TEST(StringTest, ClearDynamic)
{
    const char* longStr = "This string is definitely longer than SSO_BUFFER_SIZE";
    String s(longStr);
    EXPECT_TRUE(s.isDynamic());

    s.clear();

    EXPECT_EQ(s.length(), 0u);
    EXPECT_STREQ(s.c_str(), NULL);
    EXPECT_TRUE(s.isDynamic());
    EXPECT_EQ(s.capacity(), 0);
    EXPECT_TRUE(s.empty());
}

TEST(StringTest, ClearEmptyString)
{
    String s;
    EXPECT_TRUE(s.empty());

    s.clear();

    EXPECT_EQ(s.length(), 0u);
    EXPECT_STREQ(s.c_str(), "");
    EXPECT_FALSE(s.isDynamic());
    EXPECT_TRUE(s.empty());
}

TEST(StringTest, ClearAndPushBack)
{
    String s("Hello");
    s.clear();
    s.push_back('A');

    EXPECT_EQ(s.length(), 1u);
    EXPECT_STREQ(s.c_str(), "A");
    EXPECT_FALSE(s.isDynamic());
}

TEST(StringTest, BeginEndStatic)
{
    String s("Hello");
    EXPECT_EQ(*s.begin(), 'H');
    EXPECT_EQ(*(s.end() - 1), 'o');

    std::string collected;
    for (char* it = s.begin(); it != s.end(); ++it) {
        collected += *it;
    }
    EXPECT_EQ(collected, "Hello");
}

TEST(StringTest, BeginEndDynamic)
{
    std::string longStr(50, 'x');
    String s(longStr.c_str());

    EXPECT_TRUE(s.isDynamic());
    EXPECT_EQ(s.length(), 50u);
    EXPECT_EQ(*s.begin(), 'x');
    EXPECT_EQ(*(s.end() - 1), 'x');

    size_t count = 0;
    for (char* it = s.begin(); it != s.end(); ++it) {
        EXPECT_EQ(*it, 'x');
        ++count;
    }
    EXPECT_EQ(count, s.length());
}

TEST(StringTest, BeginEndAfterPushBack)
{
    String s("Hi");
    s.push_back('!');
    s.push_back('A');
    EXPECT_FALSE(s.isDynamic());
    std::string collected;
    for (char* it = s.begin(); it != s.end(); ++it) {
        collected += *it;
    }
    EXPECT_EQ(collected, "Hi!A");

    char buf[SSO_BUFFER_SIZE - 1];
    for (size_t i = 0; i < SSO_BUFFER_SIZE - 2; ++i) buf[i] = 'x';
    buf[SSO_BUFFER_SIZE - 2] = '\0';
    String s2(buf);
    s2.push_back('A');
    EXPECT_TRUE(s2.isDynamic());

    std::string collected2;
    for (char* it = s2.begin(); it != s2.end(); ++it) {
        collected2 += *it;
    }
    EXPECT_EQ(collected2.back(), 'A');
    EXPECT_EQ(collected2.length(), s2.length());
}

TEST(StringAppendTest, AppendStaticFits)
{
    String s("Hi");
    s.append("!");
    EXPECT_STREQ(s.c_str(), "Hi!");
    EXPECT_EQ(s.length(), 3u);
    EXPECT_FALSE(s.isDynamic());

    s.append("A");
    EXPECT_STREQ(s.c_str(), "Hi!A");
    EXPECT_EQ(s.length(), 4u);
    EXPECT_FALSE(s.isDynamic());
}

TEST(StringAppendTest, AppendStaticToDynamic)
{
    char buf[SSO_BUFFER_SIZE - 2];
    for (size_t i = 0; i < SSO_BUFFER_SIZE - 3; ++i) buf[i] = 'x';
    buf[SSO_BUFFER_SIZE - 3] = '\0';

    String s(buf);
    EXPECT_FALSE(s.isDynamic());
    EXPECT_EQ(s.length(), SSO_BUFFER_SIZE - 3);

    s.append("A");
    s.append("A");
    EXPECT_TRUE(s.isDynamic());
    EXPECT_EQ(s.length(), SSO_BUFFER_SIZE - 1);
    EXPECT_EQ(s.c_str()[SSO_BUFFER_SIZE - 3], 'A');
    EXPECT_EQ(s.c_str()[s.length()], '\0');
}


TEST(StringAppendTest, AppendDynamic)
{
    const char* longStr = "This string is already dynamic because it's long enough";
    String s(longStr);
    EXPECT_TRUE(s.isDynamic());

    size_t oldLen = s.length();
    s.append("!");
    EXPECT_TRUE(s.isDynamic());
    EXPECT_EQ(s.length(), oldLen + 1);
    EXPECT_EQ(s.c_str()[oldLen], '!');
    EXPECT_EQ(s.c_str()[s.length()], '\0');

    s.append("??");
    EXPECT_EQ(s.c_str()[oldLen + 1], '?');
    EXPECT_EQ(s.c_str()[oldLen + 2], '?');
    EXPECT_EQ(s.c_str()[s.length()], '\0');
}

TEST(StringAppendTest, AppendEmptyString)
{
    String s;
    EXPECT_TRUE(s.empty());

    s.append("");
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.length(), 0u);
    EXPECT_STREQ(s.c_str(), "");

    s.append("Hello");
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.length(), 5u);
    EXPECT_STREQ(s.c_str(), "Hello");
}

TEST(StringAppendTest, AppendStringObject)
{
    String s1("Hello");
    String s2(", World!");
    s1.append(s2);

    EXPECT_STREQ(s1.c_str(), "Hello, World!");
    EXPECT_EQ(s1.length(), 13u);
}

TEST(StringAssignTest, AssignStaticToStatic)
{
    String a("Hi");
    String b("Hello");
    b.assign(a);

    EXPECT_STREQ(b.c_str(), "Hi");
    EXPECT_EQ(b.length(), 2u);
    EXPECT_FALSE(b.isDynamic());
}
TEST(StringAssignTest, AssignDynamicToDynamic)
{
    String a("This is long long long long long");
    String b("Another long long test string");
    EXPECT_TRUE(a.isDynamic());
    EXPECT_TRUE(b.isDynamic());

    b.assign(a);

    EXPECT_STREQ(b.c_str(), a.c_str());
    EXPECT_EQ(b.length(), a.length());
    EXPECT_TRUE(b.isDynamic());
}

TEST(StringAssignTest, AssignStaticToDynamic)
{
    String a("Hi");
    String b("This is a long string forcing dynamic");

    EXPECT_TRUE(b.isDynamic());
    EXPECT_FALSE(a.isDynamic());

    b.assign(a);

    EXPECT_STREQ(b.c_str(), "Hi");
    EXPECT_EQ(b.length(), 2u);
    EXPECT_FALSE(b.isDynamic());
}


TEST(StringAssignTest, AssignDynamicToStatic)
{
    String a("This is a long string forcing dynamic");
    String b("Hi");

    EXPECT_TRUE(a.isDynamic());
    EXPECT_FALSE(b.isDynamic());

    b.assign(a);

    EXPECT_STREQ(b.c_str(), a.c_str());
    EXPECT_TRUE(b.isDynamic());
}

TEST(StringAssignTest, AssignEmptyToStatic)
{
    String a("");
    String b("Hello");

    b.assign(a);

    EXPECT_EQ(b.length(), 0u);
    EXPECT_STREQ(b.c_str(), "");
    EXPECT_FALSE(b.isDynamic());
}

TEST(StringAssignTest, AssignEmptyToDynamic)
{
    String a("");
    String b("This is long long long2");
    EXPECT_TRUE(b.isDynamic());

    b.assign(a);

    EXPECT_EQ(b.length(), 0u);
    EXPECT_STREQ(b.c_str(), "");
    EXPECT_FALSE(b.isDynamic());
}

TEST(StringAssignTest, AssignToEmpty)
{
    String a("Hello");
    String b;

    b.assign(a);

    EXPECT_EQ(b.length(), 5u);
    EXPECT_STREQ(b.c_str(), "Hello");
    EXPECT_FALSE(b.isDynamic());
}

TEST(StringAssignTest, AssignSelf)
{
    String a("Hello");
    a.assign(a);

    EXPECT_STREQ(a.c_str(), "Hello");
    EXPECT_EQ(a.length(), 5u);
    EXPECT_FALSE(a.isDynamic());
}

TEST(StringAssignTest, AssignMovedFrom)
{
    String a("Hello");
    String b(std::move(a));

    String c("TEST");
    c.assign(b);

    EXPECT_STREQ(c.c_str(), "Hello");
    EXPECT_EQ(c.length(), 5u);
    EXPECT_EQ(a.length(), 0u);
}

TEST(StringAssignTest, MultipleAssignChain)
{
    String a("AAA");
    String b("BBBBB");
    String c("CCCCCCCCCCCC");

    b.assign(a);
    c.assign(b);

    EXPECT_STREQ(b.c_str(), "AAA");
    EXPECT_STREQ(c.c_str(), "AAA");
}

TEST(StringReserveTest, ReserveLarger)
{
    String s("Hello");
    s.reserve(50);

    EXPECT_TRUE(s.isDynamic());
    EXPECT_GE(s.capacity(), 50u);
    EXPECT_STREQ(s.c_str(), "Hello");
}

TEST(StringReserveTest, ReserveSmallerDoesNothing)
{
    String s("Hello");
    s.reserve(3);

    EXPECT_FALSE(s.isDynamic()); // stays static
    EXPECT_STREQ(s.c_str(), "Hello");
}

TEST(StringResizeTest, ResizeSmaller)
{
    String s("Hello");
    s.resize(2);

    EXPECT_STREQ(s.c_str(), "He");
    EXPECT_EQ(s.length(), 2u);
}

TEST(StringResizeTest, ResizeLarger)
{
    String s("Hi");
    s.resize(5);

    EXPECT_EQ(s.length(), 2u);
    EXPECT_STREQ(s.c_str(), "Hi\0\0\0");  // trailing zeros
}

TEST(StringAppendTest, AppendStaticStatic)
{
    String a("Hi");
    String b("Yo");

    a += b;

    EXPECT_STREQ(a.c_str(), "HiYo");
    EXPECT_EQ(a.length(), 4u);
}

TEST(StringAppendTest, AppendDynamicStatic)
{
    String a("Very very long string requiring dynamic memory");
    String b("XX");

    a += b;

    EXPECT_TRUE(a.isDynamic());
    EXPECT_TRUE(a.length() > 10u);
    EXPECT_STREQ(a.c_str(), "Very very long string requiring dynamic memoryXX");
}


TEST(StringPlusTest, PlusOperator)
{
    String a("Hello");
    String b("World");

    String c = a + b;

    EXPECT_STREQ(c.c_str(), "HelloWorld");
    EXPECT_EQ(c.length(), 10u);
}










TEST(StringFindTest, FindSuccessful)
{
    String s("HelloWorld");
    EXPECT_EQ(s.find(String("World")), 5u);
}


TEST(StringFindTest, FindWithStart)
{
    String s("ababab");
    EXPECT_EQ(s.find(String("ab"), 2), 2u);
    EXPECT_EQ(s.find(String("ab"), 3), 4u);
}

TEST(StringStartsEndsTest, StartsWith)
{
    String s("HelloWorld");

    EXPECT_TRUE(s.starts_with(String("Hello")));
    EXPECT_FALSE(s.starts_with(String("World")));
}

TEST(StringStartsEndsTest, EndsWith)
{
    String s("HelloWorld");

    EXPECT_TRUE(s.ends_with(String("World")));
    EXPECT_FALSE(s.ends_with(String("Hello")));
}

int
main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}






