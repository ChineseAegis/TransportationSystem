//#define CATCH_CONFIG_MAIN  // 让 Catch 提供 main()
#include "catch.hpp"
#include "ExpandableArrayList.hpp"  // 包含您的 ExpandableArrayList 类的头文件
#include "memory_leak.h"

TEST_CASE("ExpandableArrayList functionality", "[ExpandableArrayList]") {
    SECTION("Access and add elements") {
        ExpandableArrayList<int> list(2);  // 初始容量设置为 2
        list.add(1);
        list.add(2);

        REQUIRE(list[0] == 1);
        REQUIRE(list[1] == 2);
        REQUIRE(list.size() == 2);
    }

    SECTION("Resize list") {
        ExpandableArrayList<int> list(2);
        list.add(1);
        list.add(2);
        list.add(3);  // 这应该触发 resize

        REQUIRE(list.size() == 3);
        REQUIRE(list.getCapacity() >= 3);
        REQUIRE(list[2] == 3);
    }

    SECTION("Clear list") {
        ExpandableArrayList<int> list;
        list.add(1);
        list.add(2);
        list.Clear();

        REQUIRE(list.size() == 0);
    }

    SECTION("Out of range access") {
        ExpandableArrayList<int> list;
        list.add(1);

        REQUIRE_THROWS_AS(list[-1], std::out_of_range);
        REQUIRE_THROWS_AS(list[1], std::out_of_range);
    }
}
TEST_CASE("ExpandableArrayList tests") {
    SECTION("Test empty list") {
        ExpandableArrayList<int> list;

        REQUIRE(list.size() == 0);
        REQUIRE(list.getCapacity() == 10);

        SECTION("Test accessing elements") {
            REQUIRE_THROWS_AS(list[0], std::out_of_range);
        }

        SECTION("Test adding elements") {
            list.add(1);
            list.add(2);

            REQUIRE(list.size() == 2);
            REQUIRE(list[0] == 1);
            REQUIRE(list[1] == 2);
        }

        SECTION("Test clearing the list") {
            list.add(1);
            list.add(2);

            list.Clear();

            REQUIRE(list.size() == 0);
            REQUIRE(list.getCapacity() == 10);
        }
    }

    SECTION("Test list with initial capacity") {
        ExpandableArrayList<int> list(5);

        REQUIRE(list.size() == 0);
        REQUIRE(list.getCapacity() == 5);

        SECTION("Test adding elements") {
            for (int i = 0; i < 5; ++i) {
                list.add(i);
            }

            REQUIRE(list.size() == 5);
            REQUIRE(list.getCapacity() == 5);

            list.add(5);

            REQUIRE(list.size() == 6);
            REQUIRE(list.getCapacity() == 10);
        }

        // 其他测试...
    }

    // 其他测试...
}
TEST_CASE("ExpandableArrayList Operations1", "[ExpandableArrayList1]") {
    ExpandableArrayList<int> list;

    SECTION("Default Constructor") {
        REQUIRE(list.size() == 0);
        REQUIRE(list.getCapacity() == 10); // Assuming default capacity is 10
    }

    SECTION("Add and Access Elements") {
        list.add(1);
        list.add(2);
        REQUIRE(list[0] == 1);
        REQUIRE(list[1] == 2);
        REQUIRE_THROWS_AS(list[2], std::out_of_range);
    }

    SECTION("Resize Tests") {
        for (int i = 0; i < 15; ++i) {
            list.add(i);
        }
        REQUIRE(list.size() == 15);
        REQUIRE(list.getCapacity() >= 15);
    }

    SECTION("Clear Test") {
        list.add(1);
        list.add(2);
        list.Clear();
        //REQUIRE(list.size() == 0);
    }

    SECTION("Assignment Operator") {
        ExpandableArrayList<int> newList;
        newList = list;
        //REQUIRE(newList.size() == list.size());
        // Additional checks to ensure deep copy
    }

    // Additional sections for constructor tests, size and capacity checks, edge cases, and stress test
}