#ifndef TWOWAYLIST_HPP
#define TWOWAYLIST_HPP

#include "stack.hpp"

template <class T>
struct TwoWayNode {
    TwoWayNode<T>* next = nullptr;
    TwoWayNode<T>* prev = nullptr;

    T data;
};

/**
 * \brief TwoWayList двусвязный нециклический список
 * \details Двусвязный список с поддержкой вставки, удаления элементов.
 * Сортировкой, поиском и другими полезными свойствами.
 * \pre Класс, используемый в шаблоне должен поддерживать операторы сравнения и равенства,
 *  иметь возможность копирования и использование оператора =
 */
template <typename T>
class TwoWayList {

    TwoWayNode<T>* m_first; ///< Опорный элемент. Стоит на позиции 0
    unsigned m_size; ///< Размер списка

    //В целях быстрой работы в циклах for и прочих будем хранить эти значения:
    unsigned m_currentPos; ///< Текущая позиция
    TwoWayNode<T>* m_currentNode; ///< Текущий узел для обработки

public:
    TwoWayList(); ///< Создает пустой список
    TwoWayList(const TwoWayList<T>& other); ///< Копирует список
    TwoWayList(TwoWayList<T>&& other); ///<Перемещает список
    ~TwoWayList(); ///< Очищает список

    /**
     * \brief push_back вставляет элемент в конец
     * \param [in] data элемент для добавления
     * \remark Если список пуст, то вставка идет в начало
     */
    void push_back(const T& data);
    /**
     * \brief push_first вставляет элемент в начало, заменяя текущий опорный элемент
     * \param [in] data элемент для добавления
     * \remark Если список пуст, то вставка идет в начало
     */
    void push_first(const T& data);
    /**
     * \brief insert вставляет элемент после заданной позиции
     * \param [in] pos
     * \param [in] data элемент для добавления
     * \remark Если список пуст, то вставка идет в начало, а параметр pos игнорируется
     * \remark Если pos вне диапазона допустимых значений, то элемент не добавляется
     */
    void insert(unsigned pos, const T& data);

    /**
     * \brief remove удаляет элемент в определенной позиции
     * \param [in] pos позиция, в которой элемент будет удален
     * \remark Если элемент опорный, то следующий после него станет новым опорным элементов
     * \remark Удаление не производится, если pos больше или равен размеру списка
     */
    void remove(unsigned pos);
    /**
     * \brief removeAll удаляет все элементы с определенном значением
     * \param [in] value значение элемента для удаления
     */
    void removeAll(const T& value);

    /**
     * \brief sort сортирует элементы от маленького к большему
     */
    void sort();
    /**
     * \brief search ищет элемент с определеном значением
     * \param [in] search элемент для поиска
     * \param [out] outPos позиция элемента устанавливается в этом параметре, если поиск успешен
     * \return true - элемент найден, false - нет
     * \remark Если нет необходимости знать позицию, то outPos можно установить на nullptr
     */
    bool search(const T& search, unsigned* outPos = nullptr);

    /**
     * \brief swap меняет местами два элемента
     * \param [in] pos1 1 позиция для обмена
     * \param [in] pos2 2 позиция для обмена
     * \remark Обмен местами не производится при pos1 == pos2 или если позиция вне допустимых диапазонах
     */
    void swap(unsigned pos1, unsigned pos2);

    /**
     * \brief at получает элемент в определенной позиции
     * \param [in] pos позиция элемента
     * \return константную ссылку на элемент
     * \throw std::invalid_argument если pos >= размеру списка
     */
    const T& at(unsigned pos) const;
    /**
     * \brief operator [] получает доступ к элементу в определенной позиции
     * \param [in] pos позиция элемента
     * \return ссылка на элемент
     * \throw std::invalid_argument если pos >= размеру списка
     */
    T& operator[](unsigned pos);
    /**
     * \brief operator = копирует элементы списка правой части в список с левой стороны, удаляя из него старые
     * \param [in] other список правой стороны
     */
    void operator=(const TwoWayList<T>& other);
    /**
     * \brief operator = перемещает список с правой части в левую
     * \param [in] other список правой части (rvalue ссылка)
     */
    void operator=(TwoWayList<T>&& other);
    /**
     * \brief size получения размера списка
     * \return размер списка
     */
    unsigned size() const;

private:
    /**
     * \brief getNode получает узел элемента в определенной позиции
     * \param [in] pos позиция
     * \return узел или nullptr, если pos >= размера списка
     */
    TwoWayNode<T>* getNode(unsigned pos) const;

    /**
     * \brief findMedIndex находит индекс среднего элемента
     * \param [out] out индекс среднего элемента
     * \param [in] begin левая граница поиска
     * \param [in] end правая граница поиска
     * \return true - такой элемент найден, иначе false
     */
    bool findMedIndex(unsigned& out, unsigned begin, unsigned end);
    /**
     * \brief splitPosition находит место, где следует разделить список при сортировки
     * \param [in] medPos позиция среднего элемента
     * \param [in] begin левая граница поиска
     * \param [in] end правая граница поиска
     * \return позиция, где следует поделить список
     */
    unsigned splitPosition(unsigned medPos, unsigned begin, unsigned end);
};

template <typename T>
TwoWayList<T>::TwoWayList()
    : m_first(nullptr)
    , m_size(0)
    , m_currentPos(0)
    , m_currentNode(nullptr)
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
TwoWayList<T>::TwoWayList(TwoWayList<T>&& other)
    : TwoWayList()
{
    std::swap(m_first, other.m_first);
    std::swap(m_size, other.m_size);
    std::swap(m_currentPos, other.m_currentPos);
    std::swap(m_currentNode, other.m_currentNode);
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

        m_currentNode = m_first;
        m_currentPos = 0;
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
    m_currentNode = m_first;
    m_currentPos = 0;
    m_size++;
}

template <typename T>
void TwoWayList<T>::insert(unsigned pos, const T& data)
{
    if (!m_first) {
        m_first = new TwoWayNode<T>;
        m_first->data = data;

        m_currentNode = m_first;
        m_currentPos = 0;
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
    if (pos == 0 && m_size == 1) {
        delete m_first;
        m_first = nullptr;
        m_size--;
        m_currentNode = nullptr;
        m_currentPos = 0;
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

        if (m_currentNode == nodeToDelete) {
            m_currentNode = m_first;
            m_currentPos = 0;
        }

        delete nodeToDelete;
        m_size--;
    }
}

template <typename T>
void TwoWayList<T>::removeAll(const T& value)
{
    T val = T(value);
    unsigned pos = 0;
    while (search(val, &pos)) {
        remove(pos);
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
bool TwoWayList<T>::search(const T& search, unsigned* outPos)
{
    auto currentNode = m_first;
    unsigned pos = 0;
    while (currentNode) {
        if (search == currentNode->data) {
            if (outPos)
                *outPos = pos;
            return true;
        }
        pos++;
        currentNode = currentNode->next;
    }
    return false;
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
    while (m_size != 0) {
        remove(0);
    }

    for (unsigned i = 0; i < other.size(); i++) {
        push_back(other.at(i));
    }
}

template <typename T>
void TwoWayList<T>::operator=(TwoWayList<T>&& other)
{
    std::swap(m_first, other.m_first);
    std::swap(m_size, other.m_size);
    std::swap(m_currentPos, other.m_currentPos);
    std::swap(m_currentNode, other.m_currentNode);
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
        long delta = static_cast<long>(pos) - static_cast<long>(m_currentPos);

        if (delta == 0)
            return m_currentNode;
        else if (delta > 0) {
            for (long i = delta; i > 0; i--) {
                const_cast<TwoWayList<T>*>(this)->m_currentPos++;
                const_cast<TwoWayList<T>*>(this)->m_currentNode = m_currentNode->next;
            }
        } else if (delta < 0) {
            for (long i = delta; i < 0; i++) {
                const_cast<TwoWayList<T>*>(this)->m_currentPos--;
                const_cast<TwoWayList<T>*>(this)->m_currentNode = m_currentNode->prev;
            }
        }

        return m_currentNode;
    }
    return nullptr;
}

template <typename T>
void TwoWayList<T>::swap(unsigned pos1, unsigned pos2)
{
    if (pos1 == pos2)
        return;
    if (pos1 > pos2) {
        swap(pos2, pos1);
        return;
    }

    auto node1 = getNode(pos1);
    auto node2 = getNode(pos2);

    if (!node1 || !node2)
        return;

    //Алгоритм для близстоящих
    if (pos1 == pos2 - 1) {
        auto before_nodes = node1->prev;
        auto after_nodes = node2->next;

        node1->next = after_nodes;
        node1->prev = node2;
        if (after_nodes)
            after_nodes->prev = node1;

        node2->next = node1;
        node2->prev = before_nodes;
        if (before_nodes)
            before_nodes->next = node2;
    } else {
        //Алгоритм для стоящих на далеких расстояниях
        auto before_node1 = node1->prev;
        auto before_node2 = node2->prev;
        auto after_node1 = node1->next;
        auto after_node2 = node2->next;

        node1->next = after_node2;
        node1->prev = before_node2;
        if (before_node2)
            before_node2->next = node1;
        if (after_node2)
            after_node2->prev = node1;

        node2->next = after_node1;
        node2->prev = before_node1;
        if (before_node1)
            before_node1->next = node2;
        if (after_node1)
            after_node1->prev = node2;
    }

    if (node1 == m_first)
        m_first = node2;
    else if (node2 == m_first)
        m_first = node1;

    if (m_currentNode == node1) {
        m_currentPos = pos2;
    } else if (m_currentNode == node2) {
        m_currentPos = pos1;
    }

    //auto tmp = node1->data;
    //node1->data = node2->data;
    //node2->data = tmp;
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

    auto leftPos = begin;
    auto rightPos = end;

    auto left = getNode(leftPos);
    auto right = getNode(rightPos);

    while (true) {
        while (left->data < medData && leftPos <= end) {
            left = left->next;
            leftPos++;
        }
        while (right->data > medData && begin <= rightPos) {
            right = right->prev;
            rightPos--;
        }

        if (leftPos >= rightPos)
            return leftPos;

        if (left->data != right->data) {
            auto tmp = right;
            right = left;
            left = tmp;
            swap(leftPos, rightPos);
        } else {
            left = left->next;
            leftPos++; ///< Во избежания зацикливания передвигаем границу
        }
    }
}

#endif // TWOWAYLIST_HPP
