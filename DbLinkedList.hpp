#pragma once
#include"DbListNode.hpp"
//DbListNode* Search(V& x)
//void Insert(V& x) 
//bool Remove(V& x)
//void Clear() 
template<typename V>
class DbLinkedList {
protected:
	
	DbListNode<V>* Searchhelper(V x) {
		for (DbListNode<V>* i = head->rlink; i !=head;) {
			if (i->data == x) {
				return i;
			}
			i = i->rlink;
		}
		return nullptr;
	}
	void Inserthelper(V& x) {
		if (Search(x))return;
		DbListNode<V>* newNode = new DbListNode<V>(x);  
		newNode->llink = head->rlink;
		newNode->rlink = head;
		head->rlink->rlink = newNode;
		head->rlink = newNode;
		size++;
	}
	bool Removehelper(V x) {
		if (isEmpty())return false;
		DbListNode<V>* delnode = Search(x);
		if (delnode) {
			delnode->llink->rlink = delnode->rlink;
			delnode->rlink->llink = delnode->llink;
			delete delnode;
			size--;
			return true;
		}
		return false;
	}
	void Clearhelper() {
		DbListNode<V>* remnode = head->rlink;
		while(remnode != head) {
			remnode->llink->rlink = remnode->rlink;
			remnode->rlink->llink = remnode->llink;
			delete remnode;
			remnode = head->rlink;
		}
		size = 0;
	}
	
public:
	DbListNode<V>* head;
	int size;

	bool isEmpty()const {
		if (head->rlink == head && head->llink == head && size == 0)
			return true;
		else
			return false;
	}
	DbLinkedList() {
		head = new DbListNode<V>(V());
		head->rlink = head;
		head->llink = head;
		size = 0;
	}
	 DbListNode<V>* Search(V x){
		return Searchhelper(x);
	}
	void Insert(V x) {
		Inserthelper(x);
	}
	bool Remove(V x) {
		return Removehelper(x);
	}
	void Clear() {
		Clearhelper();
	}
	~DbLinkedList() {
		Clear();
		delete head;
		head = nullptr;
	}
};