/*
 * UtilitiesTime.h
 * 定义和实现计时器任务类Timer
 * @author Yan Guo 作者 郭艳<guoyan49@cug.edu.cn>
 * @date 日期 2021-10-15
 */

#pragma once
// Copyright 2020 TooYoungTooSimp <lyc@xuming.studio>, All rights reserved.
#define _CRT_SECURE_NO_WARNINGS
#ifndef _TIMEUTILS_H_
#define _TIMEUTILS_H_
#include <chrono>

class Timer
{
public:
    using fmilliseconds = std::chrono::duration<double, std::milli>;
    void start() { t1 = std::chrono::steady_clock::now(); }
    void stop() { t2 = std::chrono::steady_clock::now(); }
    std::chrono::steady_clock::duration::rep difference() { return (t2 - t1).count(); }
    double diff_in_ms() { return std::chrono::duration_cast<fmilliseconds>(t2 - t1).count(); }

private:
    std::chrono::time_point<std::chrono::steady_clock> t1, t2;
};

#endif