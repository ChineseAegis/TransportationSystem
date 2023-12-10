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