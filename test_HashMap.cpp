#include "catch.hpp"
#include "ExpandableArrayList.hpp"  // 包含您的 ExpandableArrayList 类的头文件
#include "memory_leak.h"
#include"HashMap.hpp"

TEST_CASE("HashMap tests", "[HashMap]") {
    SECTION("Default constructor") {
        HashMap<int, int> map;
        REQUIRE(map.getSize() == 0);
    }

    SECTION("Constructor with initial size") {
        HashMap<int, int> map(50);
        REQUIRE(map.getSize() == 0);
    }

    SECTION("Constructor with initial size and load factor") {
        HashMap<int, double> map(50, 0.75);
        REQUIRE(map.getSize() == 0);
    }

    SECTION("Insert and Retrieve") {
        HashMap<std::string, int> map;
        map.Insert({ "apple", 5 });
        map.Insert({ "banana", 10 });

        REQUIRE(map.getValue("apple") == 5);
        REQUIRE(map.getValue("banana") == 10);
    }

    SECTION("Contains Key") {
        HashMap<int, std::string> map;
        map.Insert({ 1, "one" });
        REQUIRE(map.containsKey(1) == true);
        REQUIRE(map.containsKey(2) == false);
    }

    SECTION("Remove Key") {
        HashMap<int, std::string> map;
        map.Insert({ 1, "one" });
        map.Remove(1);
        REQUIRE(map.containsKey(1) == false);
    }

    SECTION("Clear HashMap") {
        HashMap<int, std::string> map;
        map.Insert({ 1, "one" });
        map.Insert({ 2, "two" });
        map.Clear();
        REQUIRE(map.getSize() == 0);
    }

    SECTION("Key Set") {
        HashMap<int, std::string> map;
        map.Insert({ 1, "one" });
        map.Insert({ 2, "two" });
        auto keySet = map.keySet();
        REQUIRE(keySet.size() == 2);
        REQUIRE(keySet.find(1) != keySet.end());
        REQUIRE(keySet.find(2) != keySet.end());
    }

    // Additional tests can be added here as necessary
}