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
TEST_CASE("DbLinkedList Tests", "[DbLinkedList]") {
    SECTION("Constructor and isEmpty") {
        DbLinkedList<int> list;
        REQUIRE(list.isEmpty() == true);
    }

    SECTION("Insert and Search") {
        DbLinkedList<int> list;
        list.Insert(1);
        REQUIRE(list.Search(1) != nullptr);
        REQUIRE(list.Search(2) == nullptr);
    }

    SECTION("Remove") {
        DbLinkedList<int> list;
        list.Insert(1);
        REQUIRE(list.Remove(1) == true);
        REQUIRE(list.Search(1) == nullptr);
        REQUIRE(list.Remove(1) == false);
    }

    SECTION("Multiple Inserts and Removes") {
        DbLinkedList<int> list;
        list.Insert(1);
        list.Insert(2);
        list.Insert(3);
        REQUIRE(list.Remove(2) == true);
        REQUIRE(list.Search(2) == nullptr);
        REQUIRE(list.Search(1) != nullptr);
        REQUIRE(list.Search(3) != nullptr);
    }

    SECTION("Clear") {
        DbLinkedList<int> list;
        list.Insert(1);
        list.Insert(2);
        list.Clear();
        REQUIRE(list.isEmpty() == true);
        REQUIRE(list.Search(1) == nullptr);
        REQUIRE(list.Search(2) == nullptr);
    }

    SECTION("Destructor") {
        DbLinkedList<int>* list = new DbLinkedList<int>();
        list->Insert(1);
        delete list;
        // 由于析构函数没有返回值，这里只能确保程序没有崩溃
        // 在实际应用中，可以使用更复杂的方法来测试析构函数
    }
}