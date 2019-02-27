#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>

template <class T>
class Stack {
private:
    struct StackNode {
        T data = 0;
        StackNode* next = nullptr;
    };

    StackNode* m_top;

public:
    Stack();
    Stack(const Stack&) = delete;
    ~Stack();

    void push(T data);
    T pop();

    bool isEmpty() const;
};

#endif // STACK_HPP

template <class T>
Stack<T>::Stack()
    : m_top(nullptr)
{
}

template <class T>
Stack<T>::~Stack()
{
    while (m_top) {
        pop();
    }
}

template <class T>
void Stack<T>::push(T data)
{
    auto new_node = new StackNode;
    new_node->data = data;
    if (!m_top) {
        new_node->next = nullptr;
    } else {
        new_node->next = m_top;
    }
    m_top = new_node;
}

template <class T>
T Stack<T>::pop()
{
    if (!m_top)
        throw std::runtime_error("Poping from empty stack");
    T out = m_top->data;
    StackNode* our_top = m_top;
    if (our_top->next) {
        m_top = our_top->next;
    } else {
        m_top = nullptr;
    }
    delete our_top;
    our_top = nullptr;
    return out;
}

template <class T>
bool Stack<T>::isEmpty() const
{
    return !m_top;
}
