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

class TestHashClass {
public:
    unsigned m_key;
    int someData;

public:
    TestHashClass()
        : TestHashClass(0, 0)
    {
    }
    //TestClass(const TestClass& other) = default;
    TestHashClass(unsigned k, int d)
        : m_key(k)
        , someData(d)
    {
    }

    TestKey key() const { return m_key; }
};

TEST(HashTable, AddingEqual)
{
    TestHashClass test(1, 1);
    HashTable<TestHashClass> table(MAX_TEST_KEY);

    ASSERT_TRUE(table.add(test));

    ASSERT_FALSE(table.add(test));
}

TEST(HashTable, AddingOverflow)
{
    srand(time(nullptr));
    HashTable<TestHashClass> table(MAX_TEST_KEY);

    TestHashClass toAdd;
    unsigned count = 0;
    while (table.add(toAdd)) {
        toAdd = TestHashClass(static_cast<unsigned>(rand()), rand());
        count++;

        ASSERT_LE(count, unsigned(MAX_TEST_KEY));
    }
}

TEST(HashTable, Getting)
{
    HashTable<TestHashClass> table(MAX_TEST_KEY);

    const unsigned count = MAX_TEST_KEY;
    const unsigned step = 3;
    unsigned countOfInsertes = 0;

    for (unsigned i = 0; i < step * count; i += step) {
        auto toAdd = TestHashClass(static_cast<unsigned>(i), static_cast<int>(i));
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
    HashTable<TestHashClass> table(MAX_TEST_KEY);

    const unsigned count = MAX_TEST_KEY;
    const unsigned step = 3;
    unsigned countOfInsertes = 0;

    for (unsigned i = 0; i < step * count; i += step) {
        auto toAdd = TestHashClass(static_cast<unsigned>(i), static_cast<int>(i));
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
