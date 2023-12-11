
#include "catch.hpp"
#include "ExpandableLinkedHashTable.hpp"
#include "memory_leak.h"
struct TestStruct {
    int key;
    std::string value;

    bool operator==(const TestStruct& other) const {
        return key == other.key && value == other.value;
    }
};

// Define a hash specialization for TestStruct
namespace std {
    template <>
    struct hash<TestStruct> {
        size_t operator()(const TestStruct& t) const {
            return hash<int>()(t.key);
        }
    };
};
TEST_CASE("Constructor and basic operations") {
    ExpandableLinkedHashTable<int, TestStruct> hashTable;

    SECTION("Initial size and capacity") {
        REQUIRE(hashTable.getSize() == 16);
        REQUIRE(hashTable.getCapcity() == 0);
    }

    SECTION("Insert and Search operations") {
        TestStruct ts = { 1, "one" };
        REQUIRE(hashTable.Insert(ts));
        REQUIRE(hashTable.Search(ts.key));
    }

    SECTION("Remove operation") {
        TestStruct ts = { 2, "two" };
        hashTable.Insert(ts);
        TestStruct removed;
        REQUIRE(hashTable.Remove(ts.key, removed));
        REQUIRE(removed == ts);
        REQUIRE_FALSE(hashTable.Search(ts.key));
    }
}
TEST_CASE("Resizing of hash table") {
    ExpandableLinkedHashTable<int, TestStruct> hashTable(2, 1.0); // Smaller size for testing

    SECTION("Table resizes correctly") {
        for (int i = 0; i < 3; ++i) {
            hashTable.Insert({ i, "value" + std::to_string(i) });
        }
        REQUIRE(hashTable.getSize() > 2); // Table should have resized
    }
}
TEST_CASE("Collision handling") {
    ExpandableLinkedHashTable<int, TestStruct> hashTable;

    SECTION("Handling collisions") {
        TestStruct ts1 = { 3, "three" };
        TestStruct ts2 = { 3, "another three" }; // Same key as ts1
        hashTable.Insert(ts1);
        hashTable.Insert(ts2);
        REQUIRE(hashTable.getBucketSize(hashTable.getBucket(ts1.key)) > 1);
    }
}
TEST_CASE("Clearing the hash table") {
    ExpandableLinkedHashTable<int, TestStruct> hashTable;

    SECTION("Clear operation") {
        hashTable.Insert({ 4, "four" });
        hashTable.Insert({ 5, "five" });
        hashTable.Clear();
        REQUIRE(hashTable.getCapcity() == 0);
    }
}
TEST_CASE("Large and Complex Test") {
    ExpandableLinkedHashTable<int, TestStruct> hashTable(2, 0.75);

    SECTION("Insertion and Search for a Large Dataset") {
        const int dataSize = 10000;
        for (int i = 0; i < dataSize; ++i) {
            TestStruct ts = { i, "value" + std::to_string(i) };
            hashTable.Insert(ts);
        }

        REQUIRE(hashTable.getCapcity() == dataSize);

        for (int i = 0; i < dataSize; ++i) {
            REQUIRE(hashTable.Search(2)==true);
        }

        REQUIRE_FALSE(hashTable.Search(dataSize));
    }

    SECTION("Remove operation for a Large Dataset") {
        const int dataSize = 100000;
        for (int i = 0; i < dataSize; ++i) {
            TestStruct ts = { i, "value" + std::to_string(i) };
            REQUIRE(hashTable.Insert(ts));
        }

        REQUIRE(hashTable.getCapcity() == dataSize);

        for (int i = 0; i < dataSize; ++i) {
            TestStruct removed;
            REQUIRE(hashTable.Remove(i, removed));
            REQUIRE(removed.key == i);
        }

        REQUIRE(hashTable.getCapcity() == 0);
    }

    SECTION("Stress Test: Insertion, Resizing, and Collision Handling") {
        const int dataSize = 100000;
        for (int i = 0; i < dataSize; ++i) {
            TestStruct ts = { i, "value" + std::to_string(i) };
            REQUIRE(hashTable.Insert(ts));
        }

        REQUIRE(hashTable.getCapcity() == dataSize);

        for (int i = 0; i < dataSize; ++i) {
            REQUIRE(hashTable.Search(i));
        }

        REQUIRE_FALSE(hashTable.Search(dataSize));

        // At this point, the hash table should have resized multiple times.
    }
}