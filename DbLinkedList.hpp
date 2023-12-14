#pragma once
#include"DbListNode.hpp"
#include <stdexcept>
//DbListNode* Search(V& x)
//void Insert(V& x) 
//bool Remove(V& x)
//void Clear() 
template<typename V>
class DbLinkedList {
protected:
	
	DbListNode<V>* Searchhelper(const V& x) {
		for (DbListNode<V>* i = head->rlink; i !=head;) {
			if (i->data == x) {
				return i;
			}
			i = i->rlink;
		}
		return nullptr;
	}
	void Inserthelper(const V& x) {
		//if (Search(x))return;
		DbListNode<V>* newNode = new DbListNode<V>(x);  
		newNode->llink = head->llink;
		newNode->rlink = head;
		head->llink->rlink = newNode;
		head->llink = newNode;
		size++;
	}
	bool Removehelper(const V& x) {
		if (isEmpty())return false;
		DbListNode<V>* delnode = Searchhelper(x);
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
	DbLinkedList& operator=(const DbLinkedList& other)
	{
		
		for (DbListNode<V>*  i = other.head->rlink; i !=other.head; )
		{
			this->Insert( i->data);
			i = i->rlink;

		}
		return *this;
	}
	 DbListNode<V>* Search(const V& x){
		return Searchhelper(x);
	}
	void Insert(const V& x) {
		Inserthelper(x);
	}
	bool Remove(const V& x) {
		return Removehelper(x);
	}
	bool Remove(DbListNode<V>* delnode) {
		if (delnode == nullptr|| delnode->llink==nullptr|| delnode->rlink==nullptr||delnode==this->head)
		{
			return false;
		}
		delnode->llink->rlink = delnode->rlink;
		delnode->rlink->llink = delnode->llink;
		delete delnode;
		size--;
		return true;
	}
	void Clear() {
		Clearhelper();
	}
	DbListNode<V>* Head()
	{
		return head;
	}
	DbListNode<V>* begin()
	{
		return head->rlink;
	}
	DbListNode<V>* end()
	{
		return head->llink;
	}
	~DbLinkedList() {
		Clear();
		delete head;
		head = nullptr;
	}
};