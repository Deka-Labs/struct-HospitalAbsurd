#include "data/twowaylist.hpp"
#include "gtest/gtest.h"

TEST(TwoWayList, Copying)
{
    TwoWayList<int> first = TwoWayList<int>();
    TwoWayList<int> second = TwoWayList<int>();

    ASSERT_NO_THROW(second = TwoWayList<int>(first));
    ASSERT_EQ(second.size(), first.size());

    first.push_back(1);
    first.push_back(2);

    ASSERT_NO_THROW(second = TwoWayList<int>(first));
    ASSERT_EQ(second.size(), first.size());
    ASSERT_EQ(first.at(0), second.at(0));
    ASSERT_EQ(first.at(1), second.at(1));
}

TEST(TwoWayList, Sizeing)
{
    TwoWayList<int> list = TwoWayList<int>();

    ASSERT_EQ(list.size(), 0);

    list.push_back(0);
    ASSERT_EQ(list.size(), 1);
    list.push_first(2);
    ASSERT_EQ(list.size(), 2);
    list.insert(0, 5);
    ASSERT_EQ(list.size(), 3);

    list.remove(0);
    list.remove(0);
    ASSERT_EQ(list.size(), 1);
    list.remove(0);
    ASSERT_EQ(list.size(), 0);
}

TEST(TwoWayList, PushBack)
{
    TwoWayList<unsigned> list = TwoWayList<unsigned>();

    const unsigned count = 1000;

    for (unsigned i = 0; i < count; i++) {
        list.push_back(i);
        ASSERT_EQ(list.size(), i + 1);
    }
    for (unsigned i = 0; i < count; i++) {
        ASSERT_EQ(list.at(unsigned(i)), i);
    }
}

TEST(TwoWayList, PushFirst)
{
    TwoWayList<unsigned> list = TwoWayList<unsigned>();

    const unsigned count = 1000;

    for (unsigned i = 0; i < count; i++) {
        list.push_first(i);
        ASSERT_EQ(list.size(), i + 1);
    }
    for (unsigned i = 0; i < count; i++) {
        ASSERT_EQ(list.at(unsigned(i)), (count - 1) - i);
    }
}

TEST(TwoWayList, Insert)
{
    TwoWayList<unsigned> list = TwoWayList<unsigned>();

    const unsigned count = 1000;
    list.insert(0, 0);
    ASSERT_EQ(list.size(), 1);
    list.insert(0, count);

    for (unsigned i = 1; i < count; i++) {
        list.insert(i - 1, i);
        ASSERT_EQ(list.size(), i + 2);
    }
    for (unsigned i = 0; i < count; i++) {
        ASSERT_EQ(list.at(unsigned(i)), i);
    }

    ASSERT_EQ(list.at(count), count);
}

TEST(TwoWayList, Removing)
{
    srand(time(nullptr));
    TwoWayList<unsigned> list = TwoWayList<unsigned>();
    ASSERT_NO_THROW(list.remove(0));
    const unsigned count = 1000;

    for (unsigned i = 0; i < count; i++) {
        list.push_back(i);
        ASSERT_EQ(list.size(), i + 1);
    }

    while (list.size() != 0) {
        auto size = list.size();
        list.remove(rand() % size);
        ASSERT_EQ(list.size(), size - 1);
    }
}

TEST(TwoWayList, Swapping)
{
    TwoWayList<unsigned> list = TwoWayList<unsigned>();

    const unsigned count = 1000;

    for (unsigned i = 0; i < count; i++) {
        list.push_back(i);
        ASSERT_EQ(list.size(), i + 1);
    }

    list.swap(count / 4, 3 * count / 4);

    ASSERT_EQ(list.at(count / 4), 3 * count / 4);
    ASSERT_EQ(list.at(3 * count / 4), count / 4);

    list.swap(count / 4, 3 * count / 4);

    for (unsigned i = 0; i < count; i++) {
        ASSERT_EQ(list.at(unsigned(i)), i);
    }

    list.swap(0, count / 2);
    ASSERT_EQ(list.at(0), count / 2);
    ASSERT_EQ(list.at(count / 2), 0);

    list.swap(count / 2, 0);
    for (unsigned i = 0; i < count; i++) {
        ASSERT_EQ(list.at(unsigned(i)), i);
    }

    list.swap(0, count - 1);
    ASSERT_EQ(list.at(0), count - 1);
    ASSERT_EQ(list.at(count - 1), 0);

    list.swap(count - 1, 0);
    for (unsigned i = 0; i < count; i++) {
        ASSERT_EQ(list.at(unsigned(i)), i);
    }

    srand(time(nullptr));
    for (unsigned i = 0; i < count; i++) {
        list.swap(rand() % count, rand() % count);
    }

    for (unsigned i = 0; i < count; i++) {
        ASSERT_NO_THROW(list.at(i));
    }
}

TEST(TwoWayList, Sorting)
{
    srand(time(nullptr));
    TwoWayList<unsigned> list = TwoWayList<unsigned>();

    const unsigned count = 1000;
    for (unsigned i = 0; i < count; i++) {
        list.push_back(rand());
    }

    list.size();

    ASSERT_NO_THROW(list.sort());

    for (unsigned i = 1; i < count; i++) {
        ASSERT_LE(list.at(i - 1), list.at(i));
    }
}
