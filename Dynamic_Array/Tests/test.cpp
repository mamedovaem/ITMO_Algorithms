#include "pch.h"
#include "../Dynamic_Array/Array.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestArrayInt, TestDefaultConstructor)
{
    Array<int> a;
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.capacity(), 8);
}


TEST(TestArrayInt, TestCapacityConstructor)
{
    Array<int> a { 10 };
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.capacity(), 10);
}

TEST(TestArrayInt, TestCopyConstructor)
{
    Array<int> a;
    for (int i = 0; i < 20; ++i)
    {
        a.insert(i + 1);
    }

    Array<int> b(a);

    for (int i = 0; i < 20; ++i)
    {
        EXPECT_EQ(a[i], b[i]);
    }
}

TEST(TestArrayInt, TestMoveConstructor)
{
    Array<int> a;
    for (int i = 0; i < 20; ++i)
    {
        a.insert(i + 1);
    }

    Array<int> b(std::move(a));

    for (int i = 0; i < 20; ++i)
    {
        EXPECT_NO_THROW(b[i]);
        EXPECT_EQ(b[i], i+1);
    }
}

TEST(TestArrayInt, TestAssignmentOperator)
{
    Array<int> a;
    for (int i = 0; i < 20; ++i)
    {
        a.insert(i + 1);
    }

    Array<int> b;
    b = a;

    for (int i = 0; i < 20; ++i)
    {
        EXPECT_EQ(a[i], b[i]);
    }
}

TEST(TestArrayInt, TestInsert)
{
    Array<int> a;
    for (int i = 0; i < 5; ++i)
    {
        EXPECT_NO_THROW(a.insert(i + 1));
    }

    EXPECT_EQ(a.size(), 5);
    EXPECT_EQ(a.capacity(), 8);
}

TEST(TestArrayInt, TestIndexedInsert)
{
    Array<int> a;
    for (int i = 0; i < 20; ++i)
    {
        a.insert(i + 1);
    }

    EXPECT_NO_THROW(a.insert(0,0));
    EXPECT_NO_THROW(a.insert(10, 0));
    EXPECT_NO_THROW(a.insert(22, 0));

    EXPECT_EQ(a.size(), 23);
    EXPECT_EQ(a.capacity(), 32);
}

TEST(TestArrayInt, TestDoubleCapacity)
{
    Array<int> a;
    for (int i = 0; i < 50; ++i)
    {
        a.insert(i + 1);
    }

    EXPECT_EQ(a.size(), 50);
    EXPECT_EQ(a.capacity(), 64);
}

TEST(TestArrayInt, TestRemove)
{
    Array<int> a;
    for (int i = 0; i < 5; ++i)
    {
        a.insert(i + 1);
    }

    EXPECT_NO_THROW(a.remove(0));

    EXPECT_EQ(a.size(), 4);
    EXPECT_EQ(a[0], 2);
    EXPECT_EQ(a.capacity(), 8);
}

TEST(TestArrayInt, TestIndexOperator)
{
    Array<int> a;
    for (int i = 0; i < 5; ++i)
    {
        a.insert(i + 1);
    }

    EXPECT_NO_THROW(a[2] = 0);

    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[2], 0);
    EXPECT_EQ(a[4], 5);
}

TEST(TestArrayString, TestDefaultConstructor)
{
    Array<std::string> a;
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.capacity(), 8);
}


TEST(TestArrayString, TestCapacityConstructor)
{
    Array<std::string> a { 10 };
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.capacity(), 10);
}

TEST(TestArrayString, TestCopyConstructor)
{
    Array<std::string> a;
    for (int i = 0; i < 20; ++i)
    {
        a.insert("akdhksbhashgkgbvzbshv" + i);
    }

    Array<std::string> b(a);

    for (int i = 0; i < 20; ++i)
    {
        EXPECT_EQ(a[i], b[i]);
    }
}

TEST(TestArrayString, TestMoveConstructor)
{
    Array<std::string> a;
    for (int i = 0; i < 20; ++i)
    {
        a.insert("akdhksbhashgkgbvzbshv" + i);
    }

    Array<std::string> b(std::move(a));

    for (int i = 0; i < 20; ++i)
    {
        EXPECT_NO_THROW(b[i]);
        EXPECT_EQ(b[i], "akdhksbhashgkgbvzbshv" + i);
    }
}

TEST(TestArrayString, TestAssignmentOperator)
{
    Array<std::string> a;
    for (int i = 0; i < 20; ++i)
    {
        a.insert("akdhksbhashgkgbvzbshv" + i);
    }

    Array<std::string> b;
    b = a;

    for (int i = 0; i < 20; ++i)
    {
        EXPECT_EQ(a[i], b[i]);
    }
}

TEST(TestArrayString, TestInsert)
{
    Array<std::string> a;
    for (int i = 0; i < 5; ++i)
    {
        EXPECT_NO_THROW(a.insert("akdhksbhashgkgbvzbshv" + i));
    }

    EXPECT_EQ(a.size(), 5);
    EXPECT_EQ(a.capacity(), 8);
}

TEST(TestArrayString, TestIndexedInsert)
{
    Array<std::string> a;
    for (int i = 0; i < 20; ++i)
    {
        a.insert("akdhksbhashgkgbvzbshv" + i);
    }

    EXPECT_NO_THROW(a.insert(0,"akdhksbhashgkgbvzbshv" + 0));
    EXPECT_NO_THROW(a.insert(10, "akdhksbhashgkgbvzbshv" + 0));
    EXPECT_NO_THROW(a.insert(22,"akdhksbhashgkgbvzbshv" + 0));

    EXPECT_EQ(a.size(), 23);
    EXPECT_EQ(a.capacity(), 32);
}

TEST(TestArrayString, TestDoubleCapacity)
{
    Array<std::string> a;
    for (int i = 0; i < 50; ++i)
    {
        a.insert("akdhksbhashgkgbvzbshv" + i);
    }

    EXPECT_EQ(a.size(), 50);
    EXPECT_EQ(a.capacity(), 64);
}

TEST(TestArrayString, TestRemove)
{
    Array<std::string> a;
    for (int i = 0; i < 5; ++i)
    {
        a.insert("akdhksbhashgkgbvzbshv" + i);
    }

    EXPECT_NO_THROW(a.remove(0));

    EXPECT_EQ(a.size(), 4);
    EXPECT_EQ(a[0], "akdhksbhashgkgbvzbshv" + 1);
    EXPECT_EQ(a.capacity(), 8);
}

TEST(TestArrayString, TestIndexOperator)
{
    Array<std::string> a;
    for (int i = 0; i < 5; ++i)
    {
        a.insert("akdhksbhashgkgbvzbshv" + i);
    }

    EXPECT_NO_THROW(a[2] = "akdhksbhashgkgbvzbshv" + 0);

    EXPECT_EQ(a[0], "akdhksbhashgkgbvzbshv" + 0);
    EXPECT_EQ(a[2], "akdhksbhashgkgbvzbshv" + 0);
    EXPECT_EQ(a[4], "akdhksbhashgkgbvzbshv" + 4);
}
