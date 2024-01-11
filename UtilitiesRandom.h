/*
 * UtilitiesRandom.h
 * 定义和实现产生随机整数、随机整数数组和随机字符串数组的函数类模板
 * @author Yan Guo 作者 郭艳<guoyan49@cug.edu.cn> 
 * @data 日期 2023-12-9
 * 2024-01-05修改：增加创建一个值不重复的长度为n的随机字符串数组
 */
#pragma once

#include <random>
#include <chrono>
#include <string>
#include <set>
#define ALPHABET_SIZE 26
#define MaxStringLength 10
#define MaxIntValue 100000;//INT_MAX
using std::string;
using std::set;

 //创建长度为N的随机T类型数组
template<class T>
T* makeRandomArray(const int& N, T(*Function)(int)) {
	T* A = new T[N];
	for (int i = 0; i < N; i++) {
		A[i] = Function(i);//i+1;

	}
	// obtain a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	if (std::is_sorted(A, A + N))
		std::shuffle(A, A + N, std::default_random_engine(seed));//混洗
	return A;
}


//generateUniqueRandomStrings创建一个值不重复的长度为n的随机字符串数组
template<class T>
T* makeUniqueRandomArray(const int& N, T(*Function)(int)) {
	T* A = new T[N];
	std::set<T> uniqueStrings;
	int i = 0;

	while (uniqueStrings.size() < N) {
		std::string randomString = Function(i);
		if (uniqueStrings.find(randomString) == uniqueStrings.end()) {
			uniqueStrings.insert(randomString);
			A[i] = randomString;
			i++;
		}
	}

	return A;
}

/** 返回一个长度是随机值length的字符串（其中每个字符随机产生）*/
static std::string randomString(int n) {
	//setSeedbyClock();
	string s = "";
	int length = rand() % MaxStringLength;
	s.resize(length);

	for (int i = 0; i < length; i++) {
		s[i] = (char)((rand() % ALPHABET_SIZE) + 'a');
	}
	return s;
};

//返回一个值是1..MaxIntValue的随机整数（参数）
static int randomInt(int n) { 
	return rand() % MaxIntValue + 1;
}

//返回一个值是1..MaxIntValue的随机整数(不带参数)
static int randomInt() {
	return rand() % MaxIntValue + 1;
}

//返回一个值是1..n的随机整数（参数）
static int randomInt_n(int n) {
	return rand() % n + 1;
}

//返回一个整数，循环调用可产生有序整数数组
static int SequentialInt(int n) { 
	return n + 1;
}