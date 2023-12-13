
#include "catch.hpp"
#include "HashMap.hpp"  // �������� HashMap ʵ��
#include <unordered_map>
#include <chrono>
#include <iostream>

TEST_CASE("Performance Tests", "[performance]") {
    const int NUM_ELEMENTS = 1000000;  // ����Ԫ������

    // ׼����������
    std::vector<std::pair<int, int>> testData;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        testData.push_back({ i, i });
    }

    SECTION("Insertion Test") {
        HashMap<int, int> hashMap;
        std::unordered_map<int, int> unorderedMap;

        // Insertion for HashMap
        auto start = std::chrono::high_resolution_clock::now();
        for (auto& kv : testData) {
            hashMap.Insert(kv);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto hashMapInsertionDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "HashMap insertion time: " << hashMapInsertionDuration << " ms\n";

        // Insertion for unordered_map
        start = std::chrono::high_resolution_clock::now();
        for (auto& kv : testData) {
            unorderedMap.insert(kv);
        }
        end = std::chrono::high_resolution_clock::now();
        auto unorderedMapInsertionDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "std::unordered_map insertion time: " << unorderedMapInsertionDuration << " ms\n";

        //REQUIRE(hashMapInsertionDuration < unorderedMapInsertionDuration * 2);  // �������ܲ�಻����2��
    }

    SECTION("Lookup Test") {
        HashMap<int, int> hashMap;
        std::unordered_map<int, int> unorderedMap;

        // Pre-insertion
        for (auto& kv : testData) {
            hashMap.Insert(kv);
            unorderedMap.insert(kv);
        }

        // Lookup for HashMap
        auto start = std::chrono::high_resolution_clock::now();
        for (auto& kv : testData) {
            hashMap.getValue(kv.first);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto hashMapLookupDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "HashMap lookup time: " << hashMapLookupDuration << " ms\n";

        // Lookup for unordered_map
        start = std::chrono::high_resolution_clock::now();
        for (auto& kv : testData) {
            unorderedMap.find(kv.first);
        }
        end = std::chrono::high_resolution_clock::now();
        auto unorderedMapLookupDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "std::unordered_map lookup time: " << unorderedMapLookupDuration << " ms\n";

        //REQUIRE(hashMapLookupDuration < unorderedMapLookupDuration * 2);  // �������ܲ�಻����2��
    }

    SECTION("Deletion Test") {
        HashMap<int, int> hashMap;
        std::unordered_map<int, int> unorderedMap;

        // Pre-insertion
        for (auto& kv : testData) {
            hashMap.Insert(kv);
            unorderedMap.insert(kv);
        }

        // Deletion for HashMap
        auto start = std::chrono::high_resolution_clock::now();
        for (auto& kv : testData) {
            hashMap.Remove(kv.first);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto hashMapDeletionDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "HashMap deletion time: " << hashMapDeletionDuration << " ms\n";

        // Deletion for unordered_map
        start = std::chrono::high_resolution_clock::now();
        for (auto& kv : testData) {
            unorderedMap.erase(kv.first);
        }
        end = std::chrono::high_resolution_clock::now();
        auto unorderedMapDeletionDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "std::unordered_map deletion time: " << unorderedMapDeletionDuration << " ms\n";

        //REQUIRE(hashMapDeletionDuration < unorderedMapDeletionDuration * 2);  // �������ܲ�಻����2��
    }
}
