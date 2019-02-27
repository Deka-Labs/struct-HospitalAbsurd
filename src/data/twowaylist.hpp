#ifndef TWOWAYLIST_HPP
#define TWOWAYLIST_HPP

#include "stack.hpp"

template <class T>
struct TwoWayNode {
    TwoWayNode<T>* next = nullptr;
    TwoWayNode<T>* prev = nullptr;

    T data;
};

template <typename T>
class TwoWayList {

    TwoWayNode<T>* m_first;
    unsigned m_size;

public:
    TwoWayList();
    TwoWayList(const TwoWayList<T>& other);
    ~TwoWayList();

    void push_back(const T& data);
    void push_first(const T& data);
    void insert(unsigned pos, const T& data);

    void remove(unsigned pos);

    void sort();

    void swap(unsigned pos1, unsigned pos2);

    const T& at(unsigned pos) const;
    T& operator[](unsigned pos);
    void operator=(const TwoWayList<T>& other);
    unsigned size() const;

private:
    TwoWayNode<T>* getNode(unsigned pos) const;

    //QuickSort utils
    bool findMedIndex(unsigned& out, unsigned begin, unsigned end);
    unsigned splitPosition(unsigned medPos, unsigned begin, unsigned end);
};

#endif // TWOWAYLIST_HPP

template <typename T>
TwoWayList<T>::TwoWayList()
    : m_first(nullptr)
    , m_size(0)
{
}

template <typename T>
TwoWayList<T>::TwoWayList(const TwoWayList<T>& other)
    : TwoWayList()
{
    for (unsigned i = 0; i < other.size(); i++) {
        push_back(other.at(i));
    }
}

template <typename T>
TwoWayList<T>::~TwoWayList()
{
    while (m_size != 0) {
        remove(0);
    }
}

template <typename T>
void TwoWayList<T>::push_back(const T& data)
{
    if (!m_first) {
        m_first = new TwoWayNode<T>;
        m_first->data = data;
    } else {
        auto currentNode = getNode(m_size - 1);

        auto newNode = new TwoWayNode<T>;
        newNode->data = data;
        newNode->prev = currentNode;
        if (currentNode)
            currentNode->next = newNode;
    }

    m_size++;
}

template <typename T>
void TwoWayList<T>::push_first(const T& data)
{
    if (!m_first) {
        m_first = new TwoWayNode<T>;
        m_first->data = data;
    } else {
        auto newNode = new TwoWayNode<T>;
        newNode->data = data;
        newNode->next = m_first;
        m_first->prev = newNode;
        m_first = newNode;
    }
    m_size++;
}

template <typename T>
void TwoWayList<T>::insert(unsigned pos, const T& data)
{
    if (!m_first) {
        m_first = new TwoWayNode<T>;
        m_first->data = data;
    } else {
        auto currentNode = getNode(pos);

        if (!currentNode)
            return;

        auto nextNode = currentNode->next;

        auto newNode = new TwoWayNode<T>;
        newNode->data = data;
        newNode->next = nextNode;
        newNode->prev = currentNode;
        currentNode->next = newNode;
        if (nextNode)
            nextNode->prev = newNode;
    }
    m_size++;
}

template <typename T>
void TwoWayList<T>::remove(unsigned pos)
{
    if (m_size == 1) {
        delete m_first;
        m_first = nullptr;
        m_size--;
    } else if (m_size > 1) {
        auto nodeToDelete = getNode(pos);

        if (!nodeToDelete)
            return;

        auto prevNode = nodeToDelete->prev;
        auto nextNode = nodeToDelete->next;

        if (prevNode)
            prevNode->next = nextNode;
        if (nextNode)
            nextNode->prev = prevNode;

        if (nodeToDelete == m_first) {
            m_first = nextNode;
        }

        delete nodeToDelete;
        m_size--;
    }
}

template <typename T>
void TwoWayList<T>::sort()
{
    Stack<unsigned> beginStack;
    Stack<unsigned> endStack;
    beginStack.push(0);
    endStack.push(m_size - 1);

    while (!beginStack.isEmpty()) {
        auto begin = beginStack.pop();
        auto end = endStack.pop();

        if (begin >= end)
            continue;

        unsigned medPos = 0;

        if (findMedIndex(medPos, begin, end)) {
            unsigned splitPos = splitPosition(medPos, begin, end);

            beginStack.push(begin);
            endStack.push((splitPos > 0) ? splitPos - 1 : 0);

            beginStack.push(splitPos + 1);
            endStack.push(end);
        }
    }
}

template <typename T>
const T& TwoWayList<T>::at(unsigned pos) const
{
    auto node = getNode(pos);

    if (node) {
        return node->data;
    }

    throw std::invalid_argument("Incorrect position in TwoWayList::at()");
}

template <typename T>
T& TwoWayList<T>::operator[](unsigned pos)
{
    auto node = getNode(pos);
    if (node)
        return node->data;
    throw std::invalid_argument("Incorrect position in TwoWayList::[])");
}

template <typename T>
void TwoWayList<T>::operator=(const TwoWayList<T>& other)
{
    for (unsigned i = 0; i < other.size(); i++) {
        push_back(other.at(i));
    }
}

template <typename T>
unsigned TwoWayList<T>::size() const
{
    return m_size;
}

template <typename T>
TwoWayNode<T>* TwoWayList<T>::getNode(unsigned pos) const
{
    if (pos < m_size) {
        auto currentNode = m_first;
        for (unsigned i = 0; i < pos; i++) {
            currentNode = currentNode->next;
        }
        return currentNode;
    }
    return nullptr;
}

template <typename T>
void TwoWayList<T>::swap(unsigned pos1, unsigned pos2)
{
    if (pos1 == pos2)
        return;

    auto node1 = getNode(pos1);
    auto node2 = getNode(pos2);

    auto tmp = node1->data;
    node1->data = node2->data;
    node2->data = tmp;
}

template <typename T>
bool TwoWayList<T>::findMedIndex(unsigned& out, unsigned begin, unsigned end)
{
    if (begin == end)
        return false;
    out = begin + (end - begin) / 2;
    return true;
}

template <typename T>
unsigned TwoWayList<T>::splitPosition(unsigned medPos, unsigned begin, unsigned end)
{

    if (begin >= end)
        return 0;

    T medData = this->at(medPos);

    auto left = begin;
    auto right = end;

    while (true) {
        while (this->at(left) < medData && left <= end)
            left++;
        while (this->at(right) > medData && begin <= right)
            right--;

        if (left >= right)
            return left;

        if (this->at(left) != this->at(right)) {
            swap(left, right);
        } else {
            left++; ///< Во избежания зацикливания передвигаем границу
        }
    }
}
