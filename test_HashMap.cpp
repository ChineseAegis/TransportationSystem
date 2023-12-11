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
TEST_CASE("HashMap Operations")
{
    SECTION("Insertion and Retrieval")
    {
        HashMap<int, std::string> map;

        SECTION("Inserting elements")
        {
            map.Insert(std::make_pair(1, "One"));
            map.Insert(std::make_pair(2, "Two"));
            map.Insert(std::make_pair(3, "Three"));
            map.Insert(std::make_pair(4, "Four"));

            REQUIRE(map.containsKey(1));
            REQUIRE(map.containsKey(2));
            REQUIRE(map.containsKey(3));
            REQUIRE(map.containsKey(4));

            REQUIRE(map.getValue(1) == "One");
            REQUIRE(map.getValue(2) == "Two");
            REQUIRE(map.getValue(3) == "Three");
            REQUIRE(map.getValue(4) == "Four");
        }

        SECTION("Retrieving non-existent elements")
        {
            REQUIRE(map.containsKey(5) == false);
            REQUIRE(map.containsKey(6) == false);

            REQUIRE(map.getValue(5) == ""); // Assuming default-constructed value is empty string
            REQUIRE(map.getValue(6) == ""); // Assuming default-constructed value is empty string
        }
    }

    SECTION("Removal")
    {
        HashMap<int, std::string> map;
        map.Insert(std::make_pair(1, "One"));
        map.Insert(std::make_pair(2, "Two"));
        map.Insert(std::make_pair(3, "Three"));

        SECTION("Removing existing elements")
        {
            REQUIRE(map.containsKey(2) == true);

            std::string value = map.Remove(2);

            REQUIRE(map.containsKey(2) == false);
            REQUIRE(value == "Two");
        }

        SECTION("Removing non-existent elements")
        {
            REQUIRE(map.containsKey(4) == false);

            std::string value = map.Remove(4);

            REQUIRE(map.containsKey(4) == false);
            //REQUIRE(value == ""); // Assuming default-constructed value is empty string
        }

        SECTION("Removing element with specific value")
        {
            REQUIRE(map.containsKey(1) == true);
            REQUIRE(map.getValue(1) == "One");

            std::string value = map.Remove(1, "Two");

            REQUIRE(map.containsKey(1) == true);
            REQUIRE(map.getValue(1) == "One");
            REQUIRE(value == ""); // Value mismatch, so element is not removed

            value = map.Remove(1, "One");

            REQUIRE(map.containsKey(1) == false);
            REQUIRE(value == "One");
        }
    }

    SECTION("Clearing the HashMap")
    {
        HashMap<int, std::string> map;
        map.Insert(std::make_pair(1, "One"));
        map.Insert(std::make_pair(2, "Two"));
        map.Insert(std::make_pair(3, "Three"));

        REQUIRE(map.getSize() == 3);

        map.Clear();

        REQUIRE(map.getSize() == 0);
        REQUIRE(map.containsKey(1) == false);
        REQUIRE(map.containsKey(2) == false);
        REQUIRE(map.containsKey(3) == false);
    }

    //SECTION("Resizing the HashMap")
    //{
    //    HashMap<int, std::string> map(2); // Initial size of 2

    //    map.Insert(std::make_pair(1, "One"));
    //    map.Insert(std::make_pair(2, "Two"));

    //    REQUIRE(map.getSize() == 2);

    //    map.resizeTable();

    //    REQUIRE(map.getSize() == 4); // Size should double after resizing
    //    REQUIRE(map.containsKey(1) == true);
    //    REQUIRE(map.containsKey(2) == true);
    //}

    SECTION("Key Set")
    {
        HashMap<int, std::string> map;
        map.Insert(std::make_pair(1, "One"));
        map.Insert(std::make_pair(2, "Two"));
        map.Insert(std::make_pair(3, "Three"));

        std::set<int> keys = map.keySet();

        REQUIRE(keys.size() == 3);
        REQUIRE(keys.find(1) != keys.end());
        REQUIRE(keys.find(2) != keys.end());
        REQUIRE(keys.find(3) != keys.end());
    }
}
TEST_CASE("HashMap Tests")
{
    SECTION("Default Constructor")
    {
        HashMap<int, std::string> map;

        REQUIRE(map.getSize() == 0);
        REQUIRE(map.keySet().empty());
        REQUIRE(map.containsKey(1) == false);
        REQUIRE(map.getValue(1) == "");
        REQUIRE(map.Remove(1) == "");
    }

    SECTION("Insert and GetValue")
    {
        HashMap<int, std::string> map;
        map.Insert(std::make_pair(1, "One"));
        map.Insert(std::make_pair(2, "Two"));
        map.Insert(std::make_pair(3, "Three"));

        REQUIRE(map.getSize() == 3);
        REQUIRE(map.containsKey(1) == true);
        REQUIRE(map.containsKey(2) == true);
        REQUIRE(map.containsKey(3) == true);

        REQUIRE(map.getValue(1) == "One");
        REQUIRE(map.getValue(2) == "Two");
        REQUIRE(map.getValue(3) == "Three");
    }

    SECTION("Remove")
    {
        HashMap<int, std::string> map;
        map.Insert(std::make_pair(1, "One"));
        map.Insert(std::make_pair(2, "Two"));
        map.Insert(std::make_pair(3, "Three"));

        REQUIRE(map.getSize() == 3);

        SECTION("Remove by key")
        {
            REQUIRE(map.Remove(2) == "Two");
            REQUIRE(map.getSize() == 2);
            REQUIRE(map.containsKey(2) == false);
            REQUIRE(map.getValue(2) == "");
        }

        SECTION("Remove by key and value")
        {
            REQUIRE(map.Remove(2, "Two") == "Two");
            REQUIRE(map.getSize() == 2);
            REQUIRE(map.containsKey(2) == false);
            REQUIRE(map.getValue(2) == "");
        }

        SECTION("Remove non-existing key")
        {
            REQUIRE(map.Remove(4) == "");
            REQUIRE(map.getSize() == 3);
        }

        SECTION("Remove non-existing key and value")
        {
            REQUIRE(map.Remove(2, "Three") == "");
            REQUIRE(map.getSize() == 3);
        }
    }

    SECTION("Clear")
    {
        HashMap<int, std::string> map;
        map.Insert(std::make_pair(1, "One"));
        map.Insert(std::make_pair(2, "Two"));
        map.Insert(std::make_pair(3, "Three"));

        REQUIRE(map.getSize() == 3);

        map.Clear();

        REQUIRE(map.getSize() == 0);
        REQUIRE(map.containsKey(1) == false);
        REQUIRE(map.containsKey(2) == false);
        REQUIRE(map.containsKey(3) == false);
    }

    SECTION("Resize")
    {
        HashMap<int, std::string> map(2);
        map.Insert(std::make_pair(1, "One"));
        map.Insert(std::make_pair(2, "Two"));

        REQUIRE(map.getSize() == 2);

        map.Insert(std::make_pair(3, "Three"));

        REQUIRE(map.getSize() == 3);
        REQUIRE(map.containsKey(3) == true);
        REQUIRE(map.getValue(3) == "Three");
    }
}