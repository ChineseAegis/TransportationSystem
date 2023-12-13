#pragma once
const int defaultsize = 8;
template<typename T>
class ADeque  {
protected:
	T* elements; int head; int tail; int maxsize;
public:
	ADeque() {
		head = 0; tail = 0; maxsize = defaultsize;
		elements = new T[maxsize];
	}
	
	~ADeque() {
		Clear();
		maxsize = 0;

	}
	bool isEmpty()const {
		return tail == head;
	}
	bool isFull()const {
		return (tail + 1) % maxsize == head;
	}
	int Length()const {
		return (tail - head + maxsize) % maxsize;
	}
	void resize(int newsize) {
		if (newsize <= 0) {
			std::cerr << "非法扩容" << std::endl;
			return;
		}

		T* newarray = new T[newsize];
		if (newarray == nullptr) {
			std::cout << "内容分配失败" << std::endl;
			exit(1);
		}

		int current = head;
		for (int i = 0; i < Length(); i++) {
			newarray[i] = elements[current];
			current = (current + 1) % maxsize;
		}

		delete[] elements;
		elements = newarray;
		head = 0;
		if (newsize > maxsize)tail = maxsize - 1; // 更新 tail 以匹配新的尾部索引
		maxsize = newsize;

	}
	
	bool pushback(const T& x) {
		if (isFull())resize(2 * maxsize);
		elements[tail] = x;
		tail = (tail + 1) % maxsize;
		return true;
	}
	void pop() {
		if (isEmpty())return;
		head = (head + 1) % maxsize;
		if (maxsize >= 16) {
			if (this->Length() < (maxsize / 2)) {
				resize(Length() + 1);
				tail = maxsize - 1;
			}
		}
	}
	T front() {
		T x;
		if (isEmpty())return false;
		x = elements[head];
		return x;
	}
	void Clear() {
		delete[]elements;
		head = tail = 0;
		elements = NULL;
	}
	
};
