#ifndef BINTREE_HPP
#define BINTREE_HPP

#include "data/twowaylist.hpp"
#include <QString>
#include <stdexcept>

template <class TypeData>
struct BinTreeNode {
    TypeData data;
    BinTreeNode* left = nullptr;
    BinTreeNode* right = nullptr;
    BinTreeNode* parent = nullptr;

    int height = 1;
};
/**
 * \brief BinTree шаблонный класс для реализации бинарного дерева
 * \pre Использованный в качестве TypeData класс должен быть обязательно НЕ указателем
 * \pre Класс TypeData должен иметь метод key() const, возвращающий TypeKey
 * \pre Класс TypeData должен поддерживать копирование и использование оператора =, а также ==
 * \pre Класс TypeKey должен иметь операторы сравнения и равенства
 */

template <class TypeData, class TypeKey>
class BinTree {
private:
    BinTreeNode<TypeData>* m_root;

public:
    BinTree(); ///< Создает пустое дерево
    BinTree(const BinTree& other) = delete; ///< Копирование запрещено
    ~BinTree(); ///< Удаляет все узлы

    bool add(const TypeData& data);

    const TypeData& find(const TypeKey& key);

    void
    remove(const TypeKey& key);

    bool isEmpty() const { return !m_root; }
    BinTreeNode<TypeData>* root() const { return m_root; }

    TwoWayList<TypeData> getListInOrder() const;

private:
    bool isLeaf(BinTreeNode<TypeData>* node) const;

    BinTreeNode<TypeData>* findNode(const TypeKey& key) const;

    void removeNode(BinTreeNode<TypeData>* node);

    void swap(BinTreeNode<TypeData>* node1, BinTreeNode<TypeData>* node2);
    int parentTo(BinTreeNode<TypeData>* parent, BinTreeNode<TypeData>* node) const;

    int balance(BinTreeNode<TypeData>* node) const;
    void recalcHeight(BinTreeNode<TypeData>* node);
    void normalize(BinTreeNode<TypeData>* node);

    void bigLeftTurn(BinTreeNode<TypeData>* node);
    void bigRightTurn(BinTreeNode<TypeData>* node);
    void smallLeftTurn(BinTreeNode<TypeData>* node);
    void smallRightTurn(BinTreeNode<TypeData>* node);
};

//Realization

template <class TypeData, class TypeKey>
BinTree<TypeData, TypeKey>::BinTree()
    : m_root(nullptr)
{
}

template <class TypeData, class TypeKey>
BinTree<TypeData, TypeKey>::~BinTree()
{
    while (!isEmpty())
        removeNode(m_root);
}

template <class TypeData, class TypeKey>
bool BinTree<TypeData, TypeKey>::add(const TypeData& data)
{
    auto newNode = new BinTreeNode<TypeData>();
    newNode->data = data;

    if (isEmpty()) {
        m_root = newNode;
        return true;
    }

    auto currentNode = m_root;

    while (currentNode) {
        if (data.key() < currentNode->data.key()) {
            if (currentNode->left) {
                currentNode = currentNode->left;
                continue;
            } else {
                currentNode->left = newNode;
                newNode->parent = currentNode;
                break;
            }
        } else if (data.key() > currentNode->data.key()) {
            if (currentNode->right) {
                currentNode = currentNode->right;
                continue;
            } else {
                currentNode->right = newNode;
                newNode->parent = currentNode;
                break;
            }
        } else {
            //Элемент уже существует.
            return false;
        }
    }

    normalize(newNode);
    return true;
}

template <class TypeData, class TypeKey>
const TypeData& BinTree<TypeData, TypeKey>::find(const TypeKey& key)
{
    BinTreeNode<TypeData>* node = findNode(key);
    if (node)
        return node->data;
    throw std::invalid_argument("There's no object with that key");
}

template <class TypeData, class TypeKey>
void BinTree<TypeData, TypeKey>::remove(const TypeKey& key)
{
    BinTreeNode<TypeData>* node = findNode(key);
    if (node)
        removeNode(node);
}

template <class TypeData, class TypeKey>
TwoWayList<TypeData> BinTree<TypeData, TypeKey>::getListInOrder() const
{
    TwoWayList<TypeData> list;

    auto currentNode = m_root;

    while (currentNode) {
        while (currentNode->left && !list.search(currentNode->left->data)) {
            currentNode = currentNode->left;
        };

        if (!list.search(currentNode->data))
            list.push_back(currentNode->data);

        if (currentNode->right && !list.search(currentNode->right->data)) {
            currentNode = currentNode->right;
        } else {
            while (currentNode && list.search(currentNode->data)) {
                currentNode = currentNode->parent;
            }
        }
    }
    return list;
}

template <class TypeData, class TypeKey>
bool BinTree<TypeData, TypeKey>::isLeaf(BinTreeNode<TypeData>* node) const
{
    if (!node)
        throw std::invalid_argument("Nullptr passed to BinTree::isLeaf()");

    return !node->right && !node->left;
}

template <class TypeData, class TypeKey>
BinTreeNode<TypeData>* BinTree<TypeData, TypeKey>::findNode(const TypeKey& key) const
{
    if (isEmpty())
        return false;

    auto currentNode = m_root;

    while (currentNode) {
        if (currentNode->data.key() > key) {
            if (currentNode->left)
                currentNode = currentNode->left;
            else
                return nullptr;
        } else if (currentNode->data.key() < key) {
            if (currentNode->right)
                currentNode = currentNode->right;
            else
                return nullptr;
        } else {
            return currentNode;
        }
    }
    return nullptr;
}

template <class TypeData, class TypeKey>
void BinTree<TypeData, TypeKey>::removeNode(BinTreeNode<TypeData>* node)
{
    if (!node)
        return;

    //Если лист, то просто удаляем
    if (isLeaf(node)) {
        if (node == m_root)
            m_root = nullptr;
        else {
            auto parent = node->parent;
            int code = parentTo(parent, node);

            if (code == -1)
                parent->left = nullptr;
            else if (code == 1)
                parent->right = nullptr;

            normalize(parent);
        }
        delete node;
    } else if (node->right) {
        //Ищем самый левый узел в правом поддереве
        auto curNode = node->right;
        while (curNode->left)
            curNode = curNode->left;

        swap(curNode, node);

        removeNode(node);
    } else {
        //Удаляем м поднимаем левое поддерево
        auto newNode = node->left;
        auto parent = node->parent;
        newNode->parent = parent;

        if (!parent)
            m_root = newNode;
        else {
            int code = parentTo(parent, node);
            if (code == -1) {
                parent->left = newNode;
            } else if (code == 1) {
                parent->right = newNode;
            } else {
                throw std::runtime_error(
                    "Imposible to have no parent at this situation");
            }
        }

        normalize(newNode);

        delete node;
    }
}

template <class TypeData, class TypeKey>
void BinTree<TypeData, TypeKey>::swap(BinTreeNode<TypeData>* node1, BinTreeNode<TypeData>* node2)
{
    if (node1 == node2)
        return;

    auto parent1 = node1->parent;
    auto parent2 = node2->parent;

    if (parent1) {
        int code = parentTo(parent1, node1);

        if (code == -1)
            parent1->left = node2;
        else if (code == 1)
            parent1->right = node2;
        else
            throw std::runtime_error(
                "Imposible to have no parent at this situation");
    } else {
        m_root = node2;
    }

    if (parent2) {
        int code = parentTo(parent2, node2);

        if (code == -1)
            parent2->left = node1;
        else if (code == 1)
            parent2->right = node1;
        else
            throw std::runtime_error(
                "Imposible to have no parent at this situation");
    } else {
        m_root = node1;
    }

    node1->parent = parent2;
    node2->parent = parent1;

    auto node1L = node1->left;
    auto node1R = node1->right;
    auto node2L = node2->left;
    auto node2R = node2->right;

    node1->left = node2L;
    node1->right = node2R;
    node2->left = node1L;
    node2->right = node1R;

    if (node1L)
        node1L->parent = node2;
    if (node1R)
        node1R->parent = node2;
    if (node2L)
        node2L->parent = node1;
    if (node2R)
        node2R->parent = node1;
}

template <class TypeData, class TypeKey>
int BinTree<TypeData, TypeKey>::parentTo(BinTreeNode<TypeData>* parent, BinTreeNode<TypeData>* node) const
{
    if (!parent || !node || (!parent->left && !parent->right))
        return 0;
    if (parent->left == node) {
        return -1;
    } else if (parent->right == node) {
        return 1;
    } else {
        return 0;
    }
}

template <class TypeData, class TypeKey>
int BinTree<TypeData, TypeKey>::balance(BinTreeNode<TypeData>* node) const
{
    if (!node)
        return 0;
    auto rHeight = (node->right) ? node->right->height : 0;
    auto lHeight = (node->left) ? node->left->height : 0;
    return rHeight - lHeight;
}

template <class TypeData, class TypeKey>
void BinTree<TypeData, TypeKey>::recalcHeight(BinTreeNode<TypeData>* node)
{
    if (!node)
        return;

    int leftHeight = 0;
    int rightHeight = 0;

    if (node->left) {
        if (node->left->data.key() == node->data.key()) {
            leftHeight = 1;
        } else {
            leftHeight = node->left->height;
        }
    }
    if (node->right) {
        rightHeight = node->right->height;
    }

    if (leftHeight < rightHeight) {
        node->height = rightHeight + 1;
    } else {
        node->height = leftHeight + 1;
    }
}

template <class TypeData, class TypeKey>
void BinTree<TypeData, TypeKey>::normalize(BinTreeNode<TypeData>* node)
{
    if (!node)
        return;

    auto curNode = node;

    while (curNode) {

        recalcHeight(curNode);

        if (balance(curNode) == -2) {
            if (balance(curNode->left) <= 0)
                smallRightTurn(curNode);
            else
                bigRightTurn(curNode);
        } else if (balance(curNode) == 2) {

            if (balance(curNode->right) >= 0)
                smallLeftTurn(curNode);
            else
                bigLeftTurn(curNode);
        }

        curNode = curNode->parent;
    }
}

template <class TypeData, class TypeKey>
void BinTree<TypeData, TypeKey>::bigLeftTurn(BinTreeNode<TypeData>* node)
{
    auto nodeA = node;
    auto nodeB = node->right;
    auto nodeC = nodeB->left;

    smallRightTurn(nodeB);
    smallLeftTurn(nodeA);

    recalcHeight(nodeA);
    recalcHeight(nodeB);
    recalcHeight(nodeC);
}

template <class TypeData, class TypeKey>
void BinTree<TypeData, TypeKey>::bigRightTurn(BinTreeNode<TypeData>* node)
{
    auto nodeA = node;
    auto nodeB = node->left;
    auto nodeC = nodeB->right;

    smallLeftTurn(nodeB);
    smallRightTurn(nodeA);

    recalcHeight(nodeA);
    recalcHeight(nodeB);
    recalcHeight(nodeC);
}

template <class TypeData, class TypeKey>
void BinTree<TypeData, TypeKey>::smallLeftTurn(BinTreeNode<TypeData>* node)
{
    auto nodeA = node;
    auto parent = node->parent;
    auto nodeB = nodeA->right;

    nodeA->right = nodeB->left;
    if (nodeA->right)
        nodeA->right->parent = nodeA;
    nodeA->parent = nodeB;
    nodeB->left = nodeA;
    nodeB->parent = parent;

    recalcHeight(nodeA);
    recalcHeight(nodeB);

    if (parent == nullptr)
        m_root = nodeB;
    else if (nodeA == parent->left)
        parent->left = nodeB;
    else if (nodeA == parent->right)
        parent->right = nodeB;
    else
        throw std::runtime_error(
            "Imposible to have no parent at this situation");
}

template <class TypeData, class TypeKey>
void BinTree<TypeData, TypeKey>::smallRightTurn(BinTreeNode<TypeData>* node)
{
    auto nodeA = node;
    auto parent = node->parent;
    auto nodeB = nodeA->left;

    nodeA->left = nodeB->right;
    if (nodeA->left)
        nodeA->left->parent = nodeA;
    nodeA->parent = nodeB;
    nodeB->right = nodeA;
    nodeB->parent = parent;

    recalcHeight(nodeA);
    recalcHeight(nodeB);

    if (parent == nullptr)
        m_root = nodeB;
    else if (nodeA == parent->left)
        parent->left = nodeB;
    else if (nodeA == parent->right)
        parent->right = nodeB;
    else
        throw std::runtime_error(
            "Imposible to have no parent at this situation");
}

#endif // BINTREE_HPP
