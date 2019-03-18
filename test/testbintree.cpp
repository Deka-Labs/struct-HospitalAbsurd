#include "data/dataprocessingclasses/bintree.hpp"
#include "data/dataprocessingclasses/twowaylist.hpp"
#include <gtest/gtest.h>

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

    unsigned key() const { return m_key; }
};

bool operator==(const TestClass& left, const TestClass& right)
{
    return (right.m_key == left.m_key) && (right.someData == left.someData);
}

void printTree(BinTreeNode<TestClass>* p, int indent = 0)
{
    if (p != nullptr) {
        if (p->right) {
            printTree(p->right, indent + 4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->right)
            std::cout << " /\n"
                      << std::setw(indent) << ' ';
        std::cout << p->data.key() << "\n ";
        if (p->left) {
            std::cout << std::setw(indent) << ' ' << " \\\n";
            printTree(p->left, indent + 4);
        }
    }
}

TEST(BinTree, AddingAndFinding)
{
    BinTree<TestClass, unsigned> tree;

    const unsigned count = 1000;
    const int begin = count;

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

TEST(BinTree, Removing)
{
    srand(unsigned(time(nullptr)));

    BinTree<TestClass, unsigned> tree;

    const unsigned count = 1000;
    const int begin = count;

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

TEST(BinTree, Balancing)
{
    srand(unsigned(time(nullptr)));

    {
        BinTree<TestClass, unsigned> tree;

        for (unsigned i = 1; i <= 5; i++) {
            tree.add(TestClass(i, int(i)));
        }

        auto root = tree.root();

        ASSERT_EQ(root->data.key(), 2);
        ASSERT_EQ(root->left->data.key(), 1);
        ASSERT_EQ(root->right->data.key(), 4);
        ASSERT_EQ(root->right->left->data.key(), 3);
        ASSERT_EQ(root->right->right->data.key(), 5);
    }

    auto checkBalance = [=](BinTreeNode<TestClass>* node) -> bool {
        if (!node)
            return false;
        auto rHeight = (node->right) ? node->right->height : 0;
        auto lHeight = (node->left) ? node->left->height : 0;
        auto balance = rHeight - lHeight;
        if (balance >= 2 || balance <= -2)
            return false;
        return true;
    };

    auto makeListInOrder = [=](const BinTree<TestClass, unsigned>& tree) -> TwoWayList<BinTreeNode<TestClass>*> {
        TwoWayList<BinTreeNode<TestClass>*> list;

        auto currentNode = tree.root();

        while (currentNode) {
            while (currentNode->left && !list.search(currentNode->left)) {
                currentNode = currentNode->left;
            };

            if (!list.search(currentNode))
                list.push_back(currentNode);

            if (currentNode->right && !list.search(currentNode->right)) {
                currentNode = currentNode->right;
            } else {
                while (list.search(currentNode)) {
                    currentNode = currentNode->parent;
                }
            }
        }
        return list;
    };

    //Последовательное добавление
    {
        BinTree<TestClass, unsigned> tree;

        const unsigned count = 1000;

        for (unsigned i = 0; i < count; i++) {
            tree.add(TestClass(i, int(i)));
        }

        auto listNodes = makeListInOrder(tree);
        ASSERT_EQ(listNodes.size(), count);

        for (unsigned id = 0; id < listNodes.size(); id++) {
            auto node = listNodes.at(id);
            ASSERT_TRUE(checkBalance(node));
        }

        //Случайное удаление
        //Создаем список ключей
        TwoWayList<unsigned> keys;
        for (unsigned id = 0; id < count; id++) {
            keys.push_back(listNodes.at(id)->data.key());
        }

        for (unsigned id = 0; id < count / 2; id++) {
            auto pos = unsigned(rand()) % keys.size();
            auto key = keys.at(pos);
            tree.remove(key);
            keys.remove(pos);
        }

        ASSERT_EQ(keys.size(), count / 2);

        //Проверяем баланс

        listNodes = makeListInOrder(tree);
        ASSERT_EQ(listNodes.size(), count / 2);

        for (unsigned id = 0; id < listNodes.size(); id++) {
            auto node = listNodes.at(id);
            ASSERT_TRUE(checkBalance(node));
        }
    }

    //Случайное добавление
    {

        BinTree<TestClass, unsigned> tree;

        const unsigned count = 1000;

        for (unsigned i = 0; i < count; i++) {
            unsigned val = 0;
            do {
                val = unsigned(rand()) % count;
            } while (tree.add(TestClass(val, int(i))) != StatusCode_OK);
        }

        auto listNodes = makeListInOrder(tree);
        ASSERT_EQ(listNodes.size(), count);

        for (unsigned id = 0; id < listNodes.size(); id++) {
            auto node = listNodes.at(id);
            ASSERT_TRUE(checkBalance(node));
        }

        //Случайное удаление
        //Создаем список ключей
        TwoWayList<unsigned> keys;
        for (unsigned id = 0; id < count; id++) {
            keys.push_back(listNodes.at(id)->data.key());
        }

        for (unsigned id = 0; id < count / 2; id++) {
            auto pos = unsigned(rand()) % keys.size();
            auto key = keys.at(pos);
            tree.remove(key);
            keys.remove(pos);
        }

        ASSERT_EQ(keys.size(), count / 2);

        //Проверяем баланс

        listNodes = makeListInOrder(tree);
        ASSERT_EQ(listNodes.size(), count / 2);

        for (unsigned id = 0; id < listNodes.size(); id++) {
            auto node = listNodes.at(id);
            ASSERT_TRUE(checkBalance(node));
        }
    }
}

TEST(BinTree, AddingSameElements)
{
    BinTree<TestClass, unsigned> tree;

    const unsigned count = 1000;

    for (unsigned i = 0; i < count; i++) {
        tree.add(TestClass(i, int(i)));
    }

    for (unsigned i = 0; i < count; i++) {
        ASSERT_EQ(tree.add(TestClass(i, int(i))), StatusCode_AlreadyExist);
    }
}

TEST(BinTree, InOrderList)
{
    BinTree<TestClass, unsigned> tree;

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
