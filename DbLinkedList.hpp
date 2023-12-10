#pragma once
#include"DbListNode.hpp"
template<typename V>
class DbLinkedList {
protected:
	DbListNode<V>*head;
	int size;
	DbLinkedList() {
		head = new DbListNode<V>(V());   
		head->rlink = head;        
		head->llink = head;
		size = 0;
	}
	bool isEmpty()const {
		if (head->rlink == head && head->llink == head && size == 0)
			return true;
		else
			return false;
	}
	DbListNode* Search(V& x) {
		for (DbListNode<V>* i = head; i < size;) {
			if()
		}
	}
	~DbLinkedList(){

	}
};