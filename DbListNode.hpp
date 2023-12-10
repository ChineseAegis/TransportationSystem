#pragma once
template<typename V>
class DbListNode {
public:
	V data;
	DbListNode<V>* llink;
	DbListNode<V>*rlink;
	DbListNode() { llink = nullptr; rlink = nullptr; }
	DbListNode(V& x) { llink = nullptr; rlink = nullptr; data = x; }
	~DbLinkedList(){}
};