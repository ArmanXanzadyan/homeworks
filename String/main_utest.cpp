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

    // Moved-from s1 should be empty
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

    // Moved-from s1 should behave as empty static string
    EXPECT_EQ(s1.length(), 0u);
    EXPECT_STREQ(s1.c_str(), "");
    EXPECT_FALSE(s1.isDynamic());
}


int
main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

