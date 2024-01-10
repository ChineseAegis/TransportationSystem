
#include "catch.hpp"
#include "Tree.hpp"  // Include your Tree header file

TEST_CASE("Tree functionality tests", "[Tree]") {
    Tree<std::string, int> tree;

    
        // Testing normal insertion
        REQUIRE(tree.insert("Root") == true);
        REQUIRE(tree.insert("Child1", "Root", 1) == true);
        REQUIRE(tree.insert("Child2", "Root", 2) == true);

        // Testing insertion of a node with non-existent parent
        REQUIRE_THROWS_AS(tree.insert("Child3", "NonExistent", 3), std::runtime_error);

        // Testing insertion of a duplicate node
        REQUIRE_THROWS_AS(tree.insert("Child1", "Root", 1), std::runtime_error);
    

   
        REQUIRE(tree.getcount() == 3);
    
    tree.printWholeTree();
    
}
    
    
