#include "data/dataprocessingclasses/bintree.hpp"
#include "data/dataprocessingclasses/twowaylist.hpp"

#include <gtest/gtest.h>

///
/// Классы и объявления для тестов
///

class TestClass {
  public:
    unsigned m_key;
    int      someData;

  public:
    TestClass()
        : TestClass(0, 0) {
    }
    TestClass(const TestClass& other) = default;
    TestClass(unsigned k, int d)
        : m_key(k)
        , someData(d) {
    }

    unsigned key() const {
        return m_key;
    }
};

bool operator==(const TestClass& left, const TestClass& right) {
    return (right.m_key == left.m_key) && (right.someData == left.someData);
}

typedef BinTreeNode<TestClass> TestBinTreeNode;

class TestBinTree : public BinTree<TestClass, unsigned> {
  public:
    virtual ~TestBinTree() {
    }

    //Проверяет дерево насбалансированость
    bool validateBalance() {
        postOrderRecalcHeight();
        auto nodes = getNodesInOrder();

        for (unsigned pos = 0; pos < nodes.size(); pos++) {
            int balance = this->balance(nodes[pos]);
            if (balance <= -2 || 2 <= balance) {
                return false;
            }
        }

        return true;
    }

    //Перераcсчет высот поддеревьев в обратном порядке
    void postOrderRecalcHeight() {
        Stack<TestBinTreeNode*> stack;
        TestBinTreeNode*        lastVisited = nullptr;
        TestBinTreeNode*        node        = m_root;
        while (!stack.isEmpty() || node != nullptr) {
            if (node != nullptr) {
                stack.push(node);
                node = node->left;
            } else {
                auto popedNode = stack.pop();
                stack.push(popedNode);
                if (popedNode->right != nullptr && lastVisited != popedNode->right)
                    node = popedNode->right;
                else {
                    lastVisited = stack.pop();
                    recalcHeight(node);
                }
            }
        }
    }

    TwoWayList<TestBinTreeNode*> getNodesInOrder() {
        TwoWayList<TestBinTreeNode*> list;
        Stack<TestBinTreeNode*>      stack;
        TestBinTreeNode*             node = m_root;

        while (!stack.isEmpty() || node != nullptr) {
            if (node != nullptr) {
                stack.push(node);
                node = node->left;
            } else {
                node = stack.pop();
                list.push_back(node);
                node = node->right;
            }
        }
        return list;
    }
};

void printTree(BinTreeNode<TestClass>* p, int indent = 0) {
    if (p != nullptr) {
        if (p->right) {
            printTree(p->right, indent + 4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->right)
            std::cout << " /\n" << std::setw(indent) << ' ';
        std::cout << p->data.key() << "\n ";
        if (p->left) {
            std::cout << std::setw(indent) << ' ' << " \\\n";
            printTree(p->left, indent + 4);
        }
    }
}

///
/// Тестирование
///

TEST(BinTree, AddingAndFinding) {
    TestBinTree tree;

    const unsigned count = 1000;
    const int      begin = count;

    for (unsigned i = 0; i < count; i++) {
        auto testClass = TestClass(i, begin + int(i));
        ASSERT_EQ(tree.add(testClass), StatusCode_OK);
    }

    for (unsigned i = 0; i < count; i++) {
        TestClass testClass;
        ASSERT_NO_THROW(testClass = tree.find(i));
        ASSERT_EQ(testClass.m_key, i);
        ASSERT_EQ(testClass.someData, begin + i);
    }
}

TEST(BinTree, Removing) {
    srand(unsigned(time(nullptr)));

    TestBinTree tree;

    const unsigned count = 1000;
    const int      begin = count;

    for (unsigned i = 0; i < count; i++) {
        auto testClass = TestClass(i, begin + int(i));
        ASSERT_EQ(tree.add(testClass), StatusCode_OK);
    }
    ASSERT_FALSE(tree.isEmpty());

    TwoWayList<unsigned> keys;

    for (unsigned i = 0; i < count; i++) {
        keys.push_back(i);
    }

    while (keys.size() != 0) {
        auto key = keys.at(unsigned(rand()) % keys.size());
        ASSERT_NO_THROW(tree.remove(key));
        keys.removeAll(key);
    }

    ASSERT_TRUE(tree.isEmpty());
}

TEST(BinTree, BalancingSerial) {
    TestBinTree tree;

    const unsigned count = 1000;

    for (unsigned i = 0; i < count; i++) {
        tree.add(TestClass(i, int(i)));
    }

    ASSERT_TRUE(tree.validateBalance());

    //Удаление
    const unsigned toDelete = 500;
    ASSERT_LE(toDelete, count);

    for (unsigned id = 0; id < count; id += count / toDelete) {
        tree.remove(id);
    }

    //Проверяем баланс
    ASSERT_TRUE(tree.validateBalance());
}

TEST(BinTree, BalancingRandom) {
    srand(unsigned(time(nullptr)));

    TestBinTree tree;

    //Добавление
    const unsigned count = 1000;

    for (unsigned i = 0; i < count; i++) {
        unsigned val = 0;
        do {
            val = unsigned(rand()) % count;
        } while (tree.add(TestClass(val, int(i))) != StatusCode_OK);
    }

    auto listNodes = tree.getNodesInOrder();
    ASSERT_EQ(listNodes.size(), count);

    ASSERT_TRUE(tree.validateBalance());

    //Случайное удаление
    //Создаем список ключей
    TwoWayList<unsigned> keys;
    for (unsigned id = 0; id < count; id++) {
        keys.push_back(listNodes.at(id)->data.key());
    }

    const unsigned toDelete = 500;
    ASSERT_LT(toDelete, count);
    for (unsigned id = 0; id < count; id += count / toDelete) {
        auto pos = unsigned(rand()) % keys.size();
        auto key = keys.at(pos);
        tree.remove(key);
        keys.remove(pos);
    }

    //Проверяем баланс

    ASSERT_TRUE(tree.validateBalance());
}

TEST(BinTree, AddingSameElements) {
    TestBinTree tree;

    const unsigned count = 1000;

    for (unsigned i = 0; i < count; i++) {
        tree.add(TestClass(i, int(i)));
    }

    for (unsigned i = 0; i < count; i++) {
        ASSERT_EQ(tree.add(TestClass(i, int(i))), StatusCode_AlreadyExist);
    }
}

TEST(BinTree, InOrderList) {
    TestBinTree tree;

    auto list = tree.getListInOrder();
    ASSERT_EQ(list.size(), 0);

    srand(unsigned(time(nullptr)));

    const unsigned count = 1000;

    for (unsigned i = 0; i < count; i++) {
        unsigned val = 0;
        do {
            val = unsigned(rand());
        } while (tree.add(TestClass(val, int(i))) != StatusCode_OK);
    }

    list = tree.getListInOrder();

    for (unsigned pos = 1; pos < list.size(); pos++) {
        ASSERT_LE(list.at(pos - 1).key(), list.at(pos).key());
    }
}
