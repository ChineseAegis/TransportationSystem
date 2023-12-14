#include "catch.hpp"
#include "Forest.hpp" // 包含你的 WQUPCUFSet 类定义

TEST_CASE("Insert multiple trees in Forest", "[Forest]") {
    Forest<std::string> forest;

    // 插入第一棵树的节点
    REQUIRE(forest.insert("Root1"));
    REQUIRE(forest.insert("Child1", "Root1"));
    REQUIRE(forest.insert("Child2", "Root1"));
    REQUIRE(forest.insert("Child3", "Child2"));
    // 插入第二棵树的节点
    REQUIRE(forest.insert("Root2"));
    REQUIRE(forest.insert("ChildA", "Root2"));
    REQUIRE(forest.insert("ChildB", "Root2"));
    REQUIRE(forest.insert("ChildC", "ChildA"));
    // 插入第三棵树的节点
    REQUIRE(forest.insert("Root3"));
    REQUIRE(forest.insert("ChildQ", "Root3"));
    REQUIRE(forest.insert("ChildW", "Root3"));
    REQUIRE(forest.insert("ChildE", "ChildW"));
    REQUIRE(forest.insert("ChildR", "ChildQ"));
    // 检查是否正确插入了所有节点
    REQUIRE(forest.getCount() == 13);

    forest.printWholeForest();
}
