
#include "catch.hpp"
#include "Tree.hpp"  // Include your Tree header file

TEST_CASE("Tree functionality", "[Tree]") {
    Tree<std::string> myTree;  // 创建一个树的实例

    
        REQUIRE(myTree.insert("Root"));
        REQUIRE(myTree.insert("Child", "Root"));
        REQUIRE(myTree.insert("Child2", "Root"));
        REQUIRE(myTree.insert("Child3", "Child2"));

        REQUIRE(myTree.getcount() == 4);
    

   
        REQUIRE_THROWS_AS(myTree.insert("Child"), std::runtime_error);
    

   
        REQUIRE_THROWS_AS(myTree.insert("Child", "NonExistentParent"), std::runtime_error);
        REQUIRE_THROWS_AS(myTree.insert("Child", "Root"), std::runtime_error);
    
    myTree.printWholeTree();
    
}
