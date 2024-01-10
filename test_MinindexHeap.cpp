#include "catch.hpp"
#include "MinIndexHeap.hpp"  // 包含你的 MinIndexHeap 头文件

TEST_CASE("MinIndexHeap functionality", "[MinIndexHeap]") {
    SECTION("Heapify an array") {
        int arr[] = { 5, 3, 8, 1, 2 };
        MinIndexHeap<int> heap(arr, 5);
        int min;
        REQUIRE(heap.removeMin(min));
        REQUIRE(min == 1);
    }

    SECTION("Insert elements") {
        MinIndexHeap<int> heap(3);
        REQUIRE(heap.Insert(5));
        REQUIRE(heap.Insert(3));
        REQUIRE(heap.Insert(8));
        // Testing auto-resize
        REQUIRE(heap.Insert(4));
        int min;
        REQUIRE(heap.removeMin(min));
        REQUIRE(min == 3);
    }

    SECTION("Remove min element") {
        MinIndexHeap<int> heap(10);
        REQUIRE(heap.Insert(5));
        REQUIRE(heap.Insert(3));
        int min;
        REQUIRE(heap.removeMin(min));
        REQUIRE(min == 3);
        REQUIRE(heap.removeMin(min));
        REQUIRE(min == 5);
    }

    SECTION("Modify element") {
        MinIndexHeap<int> heap(10);
        REQUIRE(heap.Insert(5));
        REQUIRE(heap.Insert(3));
        REQUIRE(heap.Modify(1, 1)); // 修改第二个元素的值为 1
        int min;
        REQUIRE(heap.removeMin(min));
        REQUIRE(min == 1);
    }

    SECTION("Handle auto-resize on capacity exceed") {
        MinIndexHeap<int> heap(2);
        REQUIRE(heap.Insert(5));
        REQUIRE(heap.Insert(3));
        REQUIRE(heap.Insert(10)); // 应该自动扩容
        REQUIRE(heap.Insert(1));
        int min;
        REQUIRE(heap.removeMin(min));
        REQUIRE(min == 1); // 确认自动扩容后元素正确
    }
    SECTION("1") {
        MinIndexHeap<int> heap; int mov;
        heap.Insert(0);
        heap.removeMin(mov);
        std::cout << mov << std::endl;
        heap.Insert(10);
        heap.Insert(20);
        heap.removeMin(mov);
        std::cout << mov << std::endl;
        heap.Insert(15);
        heap.Insert(15);
        heap.removeMin(mov);
        std::cout << mov << std::endl;
        heap.removeMin(mov);
        std::cout << mov << std::endl;
        heap.removeMin(mov);
        std::cout << mov << std::endl;
    }
    SECTION("2") {
        MinIndexHeap<int> heap; int mov;
        heap.Insert(0);
        heap.Insert(10000);
        heap.Insert(10000);
        heap.Insert(10000);
        heap.Insert(10000);
        heap.removeMin(mov);
        std::cout << mov << std::endl;
        heap.Insert(10);
        heap.Insert(20);
        heap.removeMin(mov);
        std::cout << mov << std::endl;
        heap.Insert(15);
        heap.Insert(15);
        heap.removeMin(mov);
        std::cout << mov << std::endl;
        heap.removeMin(mov);
        std::cout << mov << std::endl;
        heap.removeMin(mov);
        std::cout << mov << std::endl;
    }
}
