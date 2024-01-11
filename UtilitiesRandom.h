/*
 * UtilitiesRandom.h
 * �����ʵ�ֲ����������������������������ַ�������ĺ�����ģ��
 * @author Yan Guo ���� ����<guoyan49@cug.edu.cn> 
 * @data ���� 2023-12-9
 * 2024-01-05�޸ģ����Ӵ���һ��ֵ���ظ��ĳ���Ϊn������ַ�������
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

 //��������ΪN�����T��������
template<class T>
T* makeRandomArray(const int& N, T(*Function)(int)) {
	T* A = new T[N];
	for (int i = 0; i < N; i++) {
		A[i] = Function(i);//i+1;

	}
	// obtain a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	if (std::is_sorted(A, A + N))
		std::shuffle(A, A + N, std::default_random_engine(seed));//��ϴ
	return A;
}


//generateUniqueRandomStrings����һ��ֵ���ظ��ĳ���Ϊn������ַ�������
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

/** ����һ�����������ֵlength���ַ���������ÿ���ַ����������*/
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

//����һ��ֵ��1..MaxIntValue�����������������
static int randomInt(int n) { 
	return rand() % MaxIntValue + 1;
}

//����һ��ֵ��1..MaxIntValue���������(��������)
static int randomInt() {
	return rand() % MaxIntValue + 1;
}

//����һ��ֵ��1..n�����������������
static int randomInt_n(int n) {
	return rand() % n + 1;
}

//����һ��������ѭ�����ÿɲ���������������
static int SequentialInt(int n) { 
	return n + 1;
}