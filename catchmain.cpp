/*ʹcatch.hpp��memory_leak.h���б��롣
 �ļ���catchmain.cpp
 ���ߣ����ޣ�guoyan49@cug.edu.cn��
 */
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "memory_leak.h"
LeakDetector::Detector detector;
TEST_CASE("test02", "[0]")
{
  std:cout << "2";
}