
#include "catch.hpp"
#include "WQUPCUFSet.hpp" // 包含你的 WQUPCUFSet 类定义

TEST_CASE("Test WQUPCUFSet functionality", "[WQUPCUFSet]") {
    WQUPCUFSet ufSet;

    SECTION("Initially all elements should be disconnected") {
        for (int i = 0; i < 999; i++) {
            REQUIRE_FALSE(ufSet.isConnected(i, i + 1));
        }
    }

    SECTION("Union and isConnected functionality") {
        ufSet.Union(0, 1);
        ufSet.Union(1, 2);
        ufSet.Union(2, 3);
        ufSet.Union(3, 4);

        REQUIRE(ufSet.isConnected(0, 4) == true);
        REQUIRE_FALSE(ufSet.isConnected(0, 5));
    }

    SECTION("Find function") {
        ufSet.Union(0, 1);
        ufSet.Union(2, 3);
        ufSet.Union(1, 3);

        REQUIRE(ufSet.find(0) == ufSet.find(3));
        REQUIRE(ufSet.find(1) == ufSet.find(2));
    }

    SECTION("Union elements in a large set") {
        for (int i = 0; i < 999; i++) {
            ufSet.Union(i, i + 1);
        }
        REQUIRE(ufSet.isConnected(0, 999) == true);
    }

    // 添加更多测试用例，以全面测试 WQUPCUFSet 的功能
}
