#include "data/stack.hpp"
#include "gtest/gtest.h"

TEST(Stack, isEmpty)
{
    Stack<int> stack;
    ASSERT_TRUE(stack.isEmpty());

    stack.push(2);
    stack.push(3);
    stack.push(-2);

    ASSERT_TRUE(!stack.isEmpty());

    stack.pop();
    stack.pop();
    stack.pop();

    ASSERT_TRUE(stack.isEmpty());
}

TEST(Stack, PushAndPop)
{
    Stack<int> stack;

    stack.push(2);
    stack.push(3);

    int v = stack.pop();
    ASSERT_EQ(v, 3);
    v = stack.pop();
    ASSERT_EQ(v, 2);

    ASSERT_ANY_THROW(stack.pop());

    stack.push(-2);
    ASSERT_TRUE(!stack.isEmpty());
}
