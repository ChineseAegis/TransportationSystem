#pragma once
#include"ExpandableLinkedHashTable.hpp"
#include"DbListNode.hpp"
#include"DbLinkedList.hpp"
#include<set>
#include <utility>
#include<unordered_set>
template<typename K,typename V>
class HashMap
{
public:
	//int BucketSize;
	//int MaxLoadFactor;
	//int Default_BucketSize=16;
	//int Default_MaxLoadFactor=0.7;
	std::unordered_set<K> s;
	struct Element
	{
		K key;
		V value;
		bool operator==(const Element &other)const
		{
			return(key == other.key) && (value == other.value);
		}
	};
	ExpandableLinkedHashTable<K, Element>* table = nullptr;
	HashMap()
	{
		/*BucketSize = Default_BucketSize;
		MaxLoadFactor = Default_MaxLoadFactor;*/
		table = new ExpandableLinkedHashTable<K, Element>();
	}
	HashMap(int initialSize)
	{
		/*BucketSize = initialSize;
		MaxLoadFactor = Default_MaxLoadFactor;*/
		table = new ExpandableLinkedHashTable<K, Element>(initialSize);
	}
	HashMap(int initialSize, double MaxLoadFactor)
	{
	/*	BucketSize = initialSize;
		this->MaxLoadFactor = MaxLoadFactor;*/
		table = new ExpandableLinkedHashTable<K, Element>(initialSize,MaxLoadFactor);
	}
	~HashMap()
	{
		table->Clear();
		delete table;
		table = nullptr;
	}

	V getValue(const K& key)
	{
		int bucket;
		V v;
		DbListNode<Element>* node = table->findPos(key, bucket);
		if (bucket != -1)
		{
		   return node->data.value;
		}
		return V();
	}
	//std::set<K> keySet()
	//{
	//	
	//	
	//}
	bool containsKey(const K& key)
	{
		return table->Search(key);
	}
	void Insert(std::pair<K, V> k_v)
	{
		Element e;
		e.key = k_v.first;
		e.value = k_v.second;
		table->Insert(e);
	}
	V Remove(const K& key)
	{
		Element e;
		if (table->Remove(key, e) != 0)
		{
			return e.value;
		}
		return V();
	}
	V Remove(const K& key, const V& val)
	{
		Element e;
		if (val==getValue(key))
		{
			table->Remove(key, e);
			return e.value;
		}
		return V();
	}
	void Clear()
	{
		table->Clear();
	}
	int getSize()
	{
		return table->getCapcity();
	}
	void resizeTable()
	{
		table->resizeTable();

	}
};