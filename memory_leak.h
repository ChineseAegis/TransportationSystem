/**
 * ÄÚ´æÐ¹Â©¼ì²â.
 *
 *   ·ëÊ«Ïé <vip_fengyou@foxmail.com>
 *   Yan Guo <guoyan49@cug.edu.cn>
 */

#ifndef __MEMORYLEAK_H__
#define __MEMORYLEAK_H__

#define CONFIG_WINDOWS_CRTDBG
#define  new   new(_NORMAL_BLOCK, __FILE__, __LINE__)

#include <crtdbg.h>
#include <iostream>
using std::cout;
using std::endl;
namespace LeakDetector {
    struct Detector {
        Detector(){
            int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
            flag |= _CRTDBG_LEAK_CHECK_DF;
            flag |= _CRTDBG_ALLOC_MEM_DF;
            _CrtSetDbgFlag(flag);
            _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
            _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
            // Change this to leaking allocation's number to break there
            _CrtSetBreakAlloc(-1);
        };
        ~Detector() {};
    };
}
#endif