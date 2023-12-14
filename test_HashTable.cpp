#include "catch.hpp"
#include "ExpandableLinkedHashTable.hpp"
#include "memory_leak.h"
#include <utility>
#include <string>

// 使用 std::pair<int, std::string> 而不是 TestStruct
typedef std::pair<int, std::string> KeyValuePair;

// Define a hash specialization for KeyValuePair (std::pair<int, std::string>)
//namespace std {
//    template <>
//    struct hash<KeyValuePair> {
//        size_t operator()(const KeyValuePair& p) const {
//            return hash<int>()(p.first);
//        }
//    };
//};

TEST_CASE("Constructor and basic operations") {
    ExpandableLinkedHashTable<int, KeyValuePair> hashTable;

    SECTION("Initial size and capacity") {
        REQUIRE(hashTable.getSize() == 16);
        REQUIRE(hashTable.getCapcity() == 0);
    }

    SECTION("Insert and Search operations") {
        KeyValuePair kv = { 1, "one" };
        REQUIRE(hashTable.Insert(kv));
        REQUIRE(hashTable.Search(kv.first));
    }

    SECTION("Remove operation") {
        KeyValuePair kv = { 2, "two" };
        hashTable.Insert(kv);
        KeyValuePair removed;
        REQUIRE(hashTable.Remove(kv.first, removed));
        REQUIRE(removed == kv);
        REQUIRE_FALSE(hashTable.Search(kv.first));
    }
}

TEST_CASE("Resizing of hash table") {
    ExpandableLinkedHashTable<int, KeyValuePair> hashTable(2, 1.0); // Smaller size for testing

    SECTION("Table resizes correctly") {
        for (int i = 0; i < 3; ++i) {
            hashTable.Insert({ i, "value" + std::to_string(i) });
        }
        REQUIRE(hashTable.getSize() > 2); // Table should have resized
    }
}

TEST_CASE("Collision handling") {
    ExpandableLinkedHashTable<int, KeyValuePair> hashTable;

    SECTION("Handling collisions") {
        KeyValuePair kv1 = { 3, "three" };
        KeyValuePair kv2 = { 3, "another three" }; // Same key as kv1
        hashTable.Insert(kv1);
        hashTable.Insert(kv2);
        REQUIRE(hashTable.getBucketSize(hashTable.getBucket(kv1.first)) == 1);
    }
}

TEST_CASE("Clearing the hash table") {
    ExpandableLinkedHashTable<int, KeyValuePair> hashTable;

    SECTION("Clear operation") {
        hashTable.Insert({ 4, "four" });
        hashTable.Insert({ 5, "five" });
        hashTable.Clear();
        REQUIRE(hashTable.getCapcity() == 0);
    }
}

TEST_CASE("Large and Complex Test") {
    ExpandableLinkedHashTable<int, KeyValuePair> hashTable(2, 0.75);

    SECTION("Insertion and Search for a Large Dataset") {
        const int dataSize = 10000;
        for (int i = 0; i < dataSize; ++i) {
            KeyValuePair kv = { i, "value" + std::to_string(i) };
            hashTable.Insert(kv);
        }

        REQUIRE(hashTable.getCapcity() == dataSize);

        for (int i = 0; i < dataSize; ++i) {
            REQUIRE(hashTable.Search(2) == true);
        }

        REQUIRE_FALSE(hashTable.Search(dataSize));
    }

    SECTION("Remove operation for a Large Dataset") {
        const int dataSize = 10000;
        for (int i = 0; i < dataSize; ++i) {
            KeyValuePair kv = { i, "value" + std::to_string(i) };
            REQUIRE(hashTable.Insert(kv));
        }

        REQUIRE(hashTable.getCapcity() == dataSize);

        for (int i = 0; i < dataSize; ++i) {
            KeyValuePair removed;
            REQUIRE(hashTable.Remove(i, removed));
            REQUIRE(removed.first == i);
        }

        REQUIRE(hashTable.getCapcity() == 0);
    }

    SECTION("Stress Test: Insertion, Resizing, and Collision Handling") {
        const int dataSize = 100000;
        for (int i = 0; i < dataSize; ++i) {
            KeyValuePair kv = { i, "value" + std::to_string(i) };
            REQUIRE(hashTable.Insert(kv));
        }

        REQUIRE(hashTable.getCapcity() == dataSize);

        for (int i = 0; i < dataSize; ++i) {
            REQUIRE(hashTable.Search(i));
        }

        REQUIRE_FALSE(hashTable.Search(dataSize));

        // At this point, the hash table should have resized multiple times.
    }
}
