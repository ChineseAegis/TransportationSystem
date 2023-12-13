
#include "catch.hpp"
#include "MinHeap.hpp" // ������� MinHeap �ඨ��

TEST_CASE("Test MinHeap functionality", "[MinHeap]") {
    MinHeap<int> minHeap;

    SECTION("Heap should be initially empty") {
        REQUIRE(minHeap.IsEmpty() == true);
    }

    SECTION("Insert elements into MinHeap") {
        REQUIRE(minHeap.Insert(5) == true);
        REQUIRE(minHeap.Insert(3) == true);
        REQUIRE(minHeap.Insert(7) == true);
        REQUIRE(minHeap.IsEmpty() == false);
    }

    SECTION("RemoveMin on MinHeap") {
        minHeap.Insert(5);
        minHeap.Insert(3);
        minHeap.Insert(7);

        int min;
        REQUIRE(minHeap.RemoveMin(min) == true);
        REQUIRE(min == 3); // 3 ����С��Ԫ��
        REQUIRE(minHeap.RemoveMin(min) == true);
        REQUIRE(min == 5); // �������� 5
    }

    SECTION("MinHeap should be not full after initialization") {
        REQUIRE(minHeap.IsFull() == false);
    }

    SECTION("MakeEmpty on MinHeap") {
        minHeap.Insert(5);
        minHeap.Insert(3);
        minHeap.MakeEmpty();
        REQUIRE(minHeap.IsEmpty() == true);
    }

    
}
