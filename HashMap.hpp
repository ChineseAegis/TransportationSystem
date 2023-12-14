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
	//struct Element
	//{
	//	K key;
	//	V value;
	//	bool operator==(const Element &other)const
	//	{
	//		return(key == other.key) && (value == other.value);
	//	}
	//};
	ExpandableLinkedHashTable<K, std::pair<K,V>>* table = nullptr;
	HashMap()
	{
		/*BucketSize = Default_BucketSize;
		MaxLoadFactor = Default_MaxLoadFactor;*/
		table = new ExpandableLinkedHashTable<K, std::pair<K, V>>();
	}
	HashMap(int initialSize)
	{
		/*BucketSize = initialSize;
		MaxLoadFactor = Default_MaxLoadFactor;*/
		table = new ExpandableLinkedHashTable<K, std::pair<K, V>>(initialSize);
	}
	HashMap(int initialSize, double MaxLoadFactor)
	{
	/*	BucketSize = initialSize;
		this->MaxLoadFactor = MaxLoadFactor;*/
		table = new ExpandableLinkedHashTable<K, std::pair<K, V>>(initialSize,MaxLoadFactor);
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
		DbListNode<std::pair<K,V>>* node = table->findPos(key, bucket);
		if (bucket != -1)
		{
		   return node->data.second;
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
	void Insert(const std::pair<K, V> &k_v)
	{	
		table->Insert(k_v);
	}
	V Remove(const K& key)
	{
		std::pair<K, V> e;
		if (table->Remove(key, e) != 0)
		{
			return e.second;
		}
		return V();
	}
	V Remove(const K& key, const V& val)
	{
		std::pair<K,V> e;
		if (val==getValue(key))
		{
			table->Remove(key, e);
			return e.second;
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