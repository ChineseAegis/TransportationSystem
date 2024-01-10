#include "catch.hpp"
#include "Forest.hpp" // 包含你的 WQUPCUFSet 类定义

TEST_CASE("Forest functionality tests", "[Forest]") {
    Forest<std::string, int> forest;

   
        REQUIRE(forest.insert("Root") == true);
        REQUIRE(forest.insert("Child1", "Root", 1) == true);
        REQUIRE(forest.insert("Child2", "Root", 2) == true);

        // Testing exception for inserting existing node
        //REQUIRE_THROWS_AS(forest.insert("Root"), std::runtime_error);

        // Testing exception for inserting with non-existent parent
        //REQUIRE_THROWS_AS(forest.insert("Child3", "NonExistent", 3), std::runtime_error);
    

   
        REQUIRE(forest.getCount() == 3);
    
    forest.printWholeForest();
    
}
    
