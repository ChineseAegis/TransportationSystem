#include "catch.hpp"
#include "DbLinkedList.hpp" 
#include "memory_leak.h"


TEST_CASE("DbLinkedList Test", "[DbLinkedList]") {

    
    DbLinkedList<int> dbList;

    
    SECTION("isEmpty() on an empty list") {
        REQUIRE(dbList.isEmpty() == true);
        REQUIRE(dbList.Search(42) == nullptr);
        REQUIRE(dbList.Remove(42) == false);
    }

    // Test case for inserting elements and checking size
    SECTION("Insert and size check") {
        dbList.Insert(10);
        dbList.Insert(20);
        dbList.Insert(30);

        REQUIRE(dbList.isEmpty() == false);
        REQUIRE(dbList.Search(20) != nullptr);
        REQUIRE(dbList.size == 3);
    }

    // Test case for removing elements
    SECTION("Remove elements") {
        dbList.Insert(5);
        dbList.Insert(15);
        dbList.Insert(25);

        REQUIRE(dbList.Remove(15) == true);
        REQUIRE(dbList.Remove(10) == false); // Not in the list
        REQUIRE(dbList.size == 2);
    }

    // Test case for clearing the list
    SECTION("Clear the list") {
        dbList.Insert(1);
        dbList.Insert(2);
        dbList.Insert(3);

        dbList.Clear();

        REQUIRE(dbList.isEmpty() == true);
        REQUIRE(dbList.size == 0);
        REQUIRE(dbList.Search(2) == nullptr);
    }
}
