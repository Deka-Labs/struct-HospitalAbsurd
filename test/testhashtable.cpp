#include "data/dataprocessingclasses/hashtable.hpp"
#include <gtest/gtest.h>

#define MAX_TEST_KEY 10000
#define MAX_DELTA 10

class TestKey : public IHashKey {
    unsigned m_key = 0;

public:
    TestKey(const unsigned& key = 0)
        : m_key(key)
    {
    }

    unsigned hash() const { return m_key % MAX_TEST_KEY; }
    unsigned dopHash() const { return m_key % MAX_DELTA + 1; }
    bool validateKey() const { return true; }
    bool operator==(const IHashKey& other) const
    {
        const TestKey& o = dynamic_cast<const TestKey&>(other);
        return m_key == o.m_key;
    }
};

class TestClass {
public:
    unsigned m_key;
    int someData;

public:
    TestClass()
        : TestClass(0, 0)
    {
    }
    TestClass(const TestClass& other) = default;
    TestClass(unsigned k, int d)
        : m_key(k)
        , someData(d)
    {
    }

    TestKey key() const { return m_key; }
};

TEST(HashTable, AddingEqual)
{
    TestClass test(1, 1);
    HashTable<TestClass> table(MAX_TEST_KEY);

    ASSERT_TRUE(table.add(test));

    ASSERT_FALSE(table.add(test));
}

TEST(HashTable, AddingOverflow)
{
    srand(time(nullptr));
    HashTable<TestClass> table(MAX_TEST_KEY);

    TestClass toAdd;
    unsigned count = 0;
    while (table.add(toAdd)) {
        toAdd = TestClass(static_cast<unsigned>(rand()), rand());
        count++;

        ASSERT_LE(count, unsigned(MAX_TEST_KEY));
    }
}

TEST(HashTable, Getting)
{
    HashTable<TestClass> table(MAX_TEST_KEY);

    const unsigned count = MAX_TEST_KEY;
    const unsigned step = 3;
    unsigned countOfInsertes = 0;

    for (unsigned i = 0; i < step * count; i += step) {
        auto toAdd = TestClass(static_cast<unsigned>(i), static_cast<int>(i));
        if (table.add(toAdd)) {
            countOfInsertes++;
        }
    }

    unsigned getted = 0;

    for (unsigned i = 0; i < step * count; i += step) {
        if (table.get(TestKey(i))) {
            getted++;
        }
    }

    ASSERT_EQ(getted, countOfInsertes);
}

TEST(HashTable, Deleting)
{
    HashTable<TestClass> table(MAX_TEST_KEY);

    const unsigned count = MAX_TEST_KEY;
    const unsigned step = 3;
    unsigned countOfInsertes = 0;

    for (unsigned i = 0; i < step * count; i += step) {
        auto toAdd = TestClass(static_cast<unsigned>(i), static_cast<int>(i));
        if (table.add(toAdd)) {
            countOfInsertes++;
        }
    }

    unsigned getted = 0;

    for (unsigned i = 0; i < step * count; i += step) {
        if (table.get(TestKey(i))) {
            getted++;
            table.del(TestKey(i));
        }
    }

    ASSERT_EQ(getted, countOfInsertes);

    getted = 0;

    for (unsigned i = 0; i < step * count; i += step) {
        if (table.get(TestKey(i))) {
            getted++;
        }
    }

    ASSERT_EQ(getted, 0);
}
