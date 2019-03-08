#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>

/**
 * \brief класс Stack
 * \details шаблонный класс позволяющий в структуре данных стек
 *  хранить некоторые данные и извлекать их по принципу LIFO
 * \pre шаблонный класс обязан иметь конструктор копирования и оператор =
 */
template <class T>
class Stack {
private:
    struct StackNode {
        T data = 0;
        StackNode* next = nullptr;
    };

    StackNode* m_top;

public:
    Stack(); ///< Создает пустой стек
    Stack(const Stack&) = delete; ///< Конструктор копирования недоступен
    ~Stack(); ///< Деструктор

    /**
     * \brief push - добавляет элемент в стек
     * \param [in] data - информация для добавления
     */
    void push(const T& data);

    /**
     * \brief pop - извлекает элемент из стека
     * \return элемент, находящийся в топе стека
     * \throw std::runtime_error если стек пуст
     */
    T pop();

    /**
     * \brief isEmpty - проаеряет пуст ли стек
     * \return true - если стек пустой, иначе false
     */
    bool isEmpty() const;
};

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
void Stack<T>::push(const T& data)
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

#endif // STACK_HPP
