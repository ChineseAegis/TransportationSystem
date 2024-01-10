//
//#include "catch.hpp"
//#include "HashMap.hpp"  // 包含您的 HashMap 实现
//#include <unordered_map>
//#include <chrono>
//#include <iostream>
//#include<string>
//#include <random>
//TEST_CASE("Performance Tests", "[performance]") {
//    const int NUM_ELEMENTS = 1000000;  // 测试元素数量
//
//    // 准备测试数据
//    std::vector<std::pair<int, int>> testData;
//    for (int i = 0; i < NUM_ELEMENTS; ++i) {
//        testData.push_back({ i, i });
//    }
//    HashMap<int, int> hashMap;
//    std::unordered_map<int, int> unorderedMap;
//
//
//        // Insertion for HashMap
//        auto start = std::chrono::high_resolution_clock::now();
//        for (auto& kv : testData) {
//            hashMap.Insert(kv);
//        }
//        auto end = std::chrono::high_resolution_clock::now();
//        auto hashMapInsertionDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//        std::cout << "HashMap insertion time: " << hashMapInsertionDuration << " ms\n";
//
//        // Insertion for unordered_map
//        start = std::chrono::high_resolution_clock::now();
//        for (auto& kv : testData) {
//            unorderedMap.insert(kv);
//        }
//        end = std::chrono::high_resolution_clock::now();
//        auto unorderedMapInsertionDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//        std::cout << "std::unordered_map insertion time: " << unorderedMapInsertionDuration << " ms\n";
//
//        //REQUIRE(hashMapInsertionDuration < unorderedMapInsertionDuration * 2);  // 假设性能差距不超过2倍
//    //}
//
//
//
//    //SECTION("Lookup Test") {
//
//
//        // Lookup for HashMap
//         start = std::chrono::high_resolution_clock::now();
//        for (auto& kv : testData) {
//            hashMap.getValue(kv.first);
//        }
//         end = std::chrono::high_resolution_clock::now();
//        auto hashMapLookupDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//        std::cout << "HashMap lookup time: " << hashMapLookupDuration << " ms\n";
//
//        // Lookup for unordered_map
//        start = std::chrono::high_resolution_clock::now();
//        for (auto& kv : testData) {
//            unorderedMap.find(kv.first);
//        }
//        end = std::chrono::high_resolution_clock::now();
//        auto unorderedMapLookupDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//        std::cout << "std::unordered_map lookup time: " << unorderedMapLookupDuration << " ms\n";
//
//
//        //REQUIRE(hashMapLookupDuration < unorderedMapLookupDuration * 2);  // 假设性能差距不超过2倍
//   // }
//
//
//        // Deletion for HashMap
//        start = std::chrono::high_resolution_clock::now();
//        for (auto& kv : testData) {
//            hashMap.Remove(kv.first);
//        }
//        end = std::chrono::high_resolution_clock::now();
//        auto hashMapDeletionDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//        std::cout << "HashMap deletion time: " << hashMapDeletionDuration << " ms\n";
//
//        // Deletion for unordered_map
//        start = std::chrono::high_resolution_clock::now();
//        for (auto& kv : testData) {
//            unorderedMap.erase(kv.first);
//        }
//        end = std::chrono::high_resolution_clock::now();
//        auto unorderedMapDeletionDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//        std::cout << "std::unordered_map deletion time: " << unorderedMapDeletionDuration << " ms\n";
//
//        //REQUIRE(hashMapDeletionDuration < unorderedMapDeletionDuration * 2);  // 假设性能差距不超过2倍
//    
//}
//
//TEST_CASE("Performance Tests with int and std::string keys", "[performance]") {
//    const int NUM_ELEMENTS = 1000000;  // 测试元素数量减少，因为字符串处理通常更慢
//
//    // 准备整数测试数据
//    std::vector<std::pair<int, int>> testDataInt;
//    for (int i = 0; i < NUM_ELEMENTS; ++i) {
//        testDataInt.push_back({ i, i });
//    }
//
//    // 准备字符串测试数据
//    std::vector<std::pair<std::string, int>> testDataString;
//    for (int i = 0; i < NUM_ELEMENTS; ++i) {
//        testDataString.push_back({ "Key" + std::to_string(i), i });
//    }
//
//
//        HashMap<std::string, int> hashMapString;
//        std::unordered_map<std::string, int> unorderedMapString;
//
//        // 插入测试
//            // Insertion for HashMap with string keys
//            auto start = std::chrono::high_resolution_clock::now();
//            for (auto& kv : testDataString) {
//                hashMapString.Insert(kv);
//            }
//            auto end = std::chrono::high_resolution_clock::now();
//            auto hashMapInsertionDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//            std::cout << "HashMap (string keys) insertion time: " << hashMapInsertionDuration << " ms\n";
//
//            // Insertion for unordered_map with string keys
//            start = std::chrono::high_resolution_clock::now();
//            for (auto& kv : testDataString) {
//                unorderedMapString.insert(kv);
//            }
//            end = std::chrono::high_resolution_clock::now();
//            auto unorderedMapInsertionDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//            std::cout << "std::unordered_map (string keys) insertion time: " << unorderedMapInsertionDuration << " ms\n";
//       
//
//        // 查找测试
//            // 类似地，对字符串键进行查找测试
//            start = std::chrono::high_resolution_clock::now();
//            for (auto& kv : testDataString) {
//                hashMapString.getValue(kv.first);
//            }
//            end = std::chrono::high_resolution_clock::now();
//            auto hashMapLookupDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//            std::cout << "HashMap (string keys) find time: " << hashMapLookupDuration << " ms\n";
//
//            // Insertion for unordered_map with string keys
//            start = std::chrono::high_resolution_clock::now();
//            for (auto& kv : testDataString) {
//                unorderedMapString.find(kv.first);
//            }
//            end = std::chrono::high_resolution_clock::now();
//            auto unorderedMapLookupDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//            std::cout << "std::unordered_map (string keys) find time: " << unorderedMapLookupDuration << " ms\n";
//        
//
//        // 删除测试
//
//    
//}
//TEST_CASE("Random Performance Tests", "[performance]") {
//    const int NUM_ELEMENTS = 1000000;  // 测试元素数量
//
//    // 准备测试数据
//    std::vector<std::pair<int, int>> testData;
//    std::random_device rd;  // Random device
//    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
//    std::uniform_int_distribution<> distrib(1, 1000000); // Range of random numbers
//
//    for (int i = 0; i < NUM_ELEMENTS; ++i) {
//        int randomKey = distrib(gen);   // Generate a random integer
//        int randomValue = distrib(gen); // Generate another random integer
//        testData.push_back({ randomKey, randomValue });
//    }
//    HashMap<int, int> hashMap;
//    std::unordered_map<int, int> unorderedMap;
//
//
//    // Insertion for HashMap
//    auto start = std::chrono::high_resolution_clock::now();
//    for (auto& kv : testData) {
//        hashMap.Insert(kv);
//    }
//    auto end = std::chrono::high_resolution_clock::now();
//    auto hashMapInsertionDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//    std::cout << "HashMap insertion time: " << hashMapInsertionDuration << " ms\n";
//
//    // Insertion for unordered_map
//    start = std::chrono::high_resolution_clock::now();
//    for (auto& kv : testData) {
//        unorderedMap.insert(kv);
//    }
//    end = std::chrono::high_resolution_clock::now();
//    auto unorderedMapInsertionDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//    std::cout << "std::unordered_map insertion time: " << unorderedMapInsertionDuration << " ms\n";
//
//    //REQUIRE(hashMapInsertionDuration < unorderedMapInsertionDuration * 2);  // 假设性能差距不超过2倍
////}
//
//
//
////SECTION("Lookup Test") {
//
//
//    // Lookup for HashMap
//    start = std::chrono::high_resolution_clock::now();
//    for (auto& kv : testData) {
//        hashMap.getValue(kv.first);
//    }
//    end = std::chrono::high_resolution_clock::now();
//    auto hashMapLookupDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//    std::cout << "HashMap lookup time: " << hashMapLookupDuration << " ms\n";
//
//    // Lookup for unordered_map
//    start = std::chrono::high_resolution_clock::now();
//    for (auto& kv : testData) {
//        unorderedMap.find(kv.first);
//    }
//    end = std::chrono::high_resolution_clock::now();
//    auto unorderedMapLookupDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//    std::cout << "std::unordered_map lookup time: " << unorderedMapLookupDuration << " ms\n";
//
//
//    //REQUIRE(hashMapLookupDuration < unorderedMapLookupDuration * 2);  // 假设性能差距不超过2倍
//// }
//
//
//     // Deletion for HashMap
//    start = std::chrono::high_resolution_clock::now();
//    for (auto& kv : testData) {
//        hashMap.Remove(kv.first);
//    }
//    end = std::chrono::high_resolution_clock::now();
//    auto hashMapDeletionDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//    std::cout << "HashMap deletion time: " << hashMapDeletionDuration << " ms\n";
//
//    // Deletion for unordered_map
//    start = std::chrono::high_resolution_clock::now();
//    for (auto& kv : testData) {
//        unorderedMap.erase(kv.first);
//    }
//    end = std::chrono::high_resolution_clock::now();
//    auto unorderedMapDeletionDuration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
//    std::cout << "std::unordered_map deletion time: " << unorderedMapDeletionDuration << " ms\n";
//}