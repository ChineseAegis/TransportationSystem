#include "catch.hpp"
#include "Forest.hpp" // ������� WQUPCUFSet �ඨ��

TEST_CASE("Insert multiple trees in Forest", "[Forest]") {
    Forest<std::string> forest;

    // �����һ�����Ľڵ�
    REQUIRE(forest.insert("Root1"));
    REQUIRE(forest.insert("Child1", "Root1"));
    REQUIRE(forest.insert("Child2", "Root1"));
    REQUIRE(forest.insert("Child3", "Child2"));
    // ����ڶ������Ľڵ�
    REQUIRE(forest.insert("Root2"));
    REQUIRE(forest.insert("ChildA", "Root2"));
    REQUIRE(forest.insert("ChildB", "Root2"));
    REQUIRE(forest.insert("ChildC", "ChildA"));
    // ������������Ľڵ�
    REQUIRE(forest.insert("Root3"));
    REQUIRE(forest.insert("ChildQ", "Root3"));
    REQUIRE(forest.insert("ChildW", "Root3"));
    REQUIRE(forest.insert("ChildE", "ChildW"));
    REQUIRE(forest.insert("ChildR", "ChildQ"));
    // ����Ƿ���ȷ���������нڵ�
    REQUIRE(forest.getCount() == 13);

    forest.printWholeForest();
}
