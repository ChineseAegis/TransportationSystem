/*使catch.hpp和memory_leak.h进行编译。
 文件：catchmain.cpp
 作者：郭艳（guoyan49@cug.edu.cn）
 */
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "memory_leak.h"
LeakDetector::Detector detector;
TEST_CASE("test02", "[0]")
{
	std::cout << "122";
}