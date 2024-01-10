#pragma once
#include"DbListNode.hpp"
#include"DbLinkedList.hpp"
#include"ExpandableArrayList.hpp"
#include"HashMap.hpp"
#include <utility>
#include <stdexcept>
#include<queue>
#include"Neighbors.hpp"
#include"Deque.hpp"
template<typename Object,typename Weight>
class WUSGraph
{
private:
	struct Vertex;
	struct Edge
	{
		std::pair<int, int> edge;
		Weight weight;
		DbListNode<Vertex>* vertex=nullptr;
		DbListNode<Edge>* buddy=nullptr;
		Edge(int vertex1=-1, int vertex2=-1, DbListNode<Vertex>* vertex=nullptr, Weight weight = 1, DbListNode<Edge>* buddy=nullptr)
		{
			edge.first = vertex1;
			edge.second = vertex2;
			this->weight = weight;
			this->buddy = buddy;
			this->vertex = vertex;
		}
	
		void clear()
		{
			if (buddy == nullptr)
			{
				return;
			}
			buddy->data.vertex->data.degree--;
			buddy->data.vertex->data.edges->Remove(buddy);
			buddy = nullptr;
			vertex->data.degree--;
		}
		~Edge()
		{
			
		}
	};
	struct Vertex
	{
		int data;
		int degree = 0;
		DbLinkedList<Edge>* edges=nullptr;
		Vertex()
		{
			edges = new DbLinkedList<Edge>();
			this->data = -1;
		}
		Vertex(int data)
		{
			edges = new DbLinkedList<Edge>();
			this->data = data;
		}
		Vertex(const Vertex& other)
		{

			data = other.data;
			edges = new DbLinkedList<Edge>();
			*edges = *(other.edges);
		}
		Vertex& operator=(const Vertex& other)
		{
			if (edges != nullptr)
			{
				delete edges;
				edges = nullptr;
			}
			data = other.data;
			edges = new DbLinkedList<Edge>();
			*edges = *(other.edges);
			return *this;
		}
		~Vertex()
		{
			if (edges != nullptr)
			{
				delete edges;
				edges = nullptr;
			}
		}
	};
	
	DbLinkedList<Vertex>* vertexs = nullptr;
	int VertexCount = 0;
	int EdgeCount = 0;
	HashMap<Object, DbListNode<Vertex>*> toVertexMap;
	HashMap<std::pair<Object, Object>, DbListNode<Edge>*> toEdgeMap;
	HashMap<int,Object > toObjectMap;
	ADeque<int> intQueue;
public:
	WUSGraph()
	{
		vertexs = new DbLinkedList<Vertex>();
	}
	~WUSGraph()
	{
		if (vertexs != nullptr)
		{
			delete vertexs;
		}
		
	}
	int vertexCount()
	{
		return VertexCount;
	}
	int edgeCount()
	{
		return EdgeCount;
	}
	void addVertex(Object object)
	{
		if (toVertexMap.containsKey(object))
		{
			throw std::runtime_error("重复的顶点"+object);
		}
		std::pair<Object,DbListNode<Vertex>*> mypair;
		mypair.first = object;

		int num;
		if (intQueue.isEmpty())
		{
			num = VertexCount + 1;
		}
		else
		{
			num = intQueue.front();
			intQueue.pop();
		}
		vertexs->Insert(Vertex(num));
		DbListNode<Vertex>* node = vertexs->end();
		mypair.second = node;
		toVertexMap.Insert(mypair);
		VertexCount++;
		toObjectMap.Insert(std::make_pair(num, object));
	}
	Neighbors<Object, Weight> getNeighbors(Object object)
	{
		if (!toVertexMap.containsKey(object))
		{
			throw std::runtime_error("不存在的点");
		}
		DbListNode<Vertex>* node = toVertexMap.getValue(object);
		Neighbors<Object, Weight> n(node->data.degree);
		DbListNode<Edge>* enode = node->data.edges->begin();
		for (int i = 0; enode != node->data.edges->Head(); i++)
		{
			Object oj = toObjectMap.getValue(enode->data.edge.second);
			n.object[i] = oj;
			n.weight[i] = enode->data.weight;
			enode = enode->rlink;
		}
		return n;
	}
	void removeVertex(Object object)
	{
		if (!toVertexMap.containsKey(object))
		{
			throw std::runtime_error("删除不存在的点");
			return;
		}
		Neighbors<Object,Weight> nei = getNeighbors(object);
		for (int i = 0; i < nei.size; i++)
		{
			toEdgeMap.Remove(std::make_pair(object, nei.object[i]));
			toEdgeMap.Remove(std::make_pair(nei.object[i], object));
		}
		DbListNode<Vertex>* node=toVertexMap.getValue(object);
		int degree = node->data.degree;
		intQueue.pushback(node->data.data);
		toObjectMap.Remove(node->data.data);
		DbListNode<Edge>* enode = node->data.edges->begin();
		while (enode != node->data.edges->begin()->llink)
		{

			enode->data.clear();
			enode = enode->rlink;
		}
		vertexs->Remove(node);
		toVertexMap.Remove(object);
		VertexCount--;
		EdgeCount = EdgeCount - degree;
	}
	bool isVertex(Object object)
	{
		return toVertexMap.containsKey(object);
	}
	void addEdge(Object object1, Object object2, Weight weight)
	{
		if (toEdgeMap.containsKey(std::make_pair(object1, object2)))
		{
			std::cout << "重复的边" + object1<< std::endl;
			std::cout << "重复的边" + object2 << std::endl;
			throw std::runtime_error("重复的边");
		}
		if (!toVertexMap.containsKey(object1)||!toVertexMap.containsKey(object2))
		{
			throw std::runtime_error("不存在的点");
		}
		DbListNode<Vertex>* node1 = toVertexMap.getValue(object1);
		DbListNode<Vertex>* node2 = toVertexMap.getValue(object2);
		int num1 = node1->data.data;
		int num2 = node2->data.data;
		Edge e1(num1, num2, node1, weight);
		Edge e2(num2, num1, node2, weight);
		node1->data.edges->Insert(e1);
		node2->data.edges->Insert(e2);
		std::pair<Object,Object> mypair1;
		mypair1.first = object1;
		mypair1.second = object2;
		std::pair<Object, Object> mypair2;
		mypair2.first = object2;
		mypair2.second = object1;
		DbListNode<Edge>* enode1 = node1->data.edges->end();
		DbListNode<Edge>* enode2 = node2->data.edges->end();
		enode1->data.buddy = enode2;
		enode2->data.buddy = enode1;
		toEdgeMap.Insert(std::make_pair(mypair1,enode1));
		toEdgeMap.Insert(std::make_pair(mypair2,enode2));
		node1->data.degree++;
		node2->data.degree++;
		EdgeCount++;
	}
	void removeEdge(Object object1, Object object2)
	{
		if (!toEdgeMap.containsKey(std::make_pair(object1, object2))||!toVertexMap.containsKey(object1)||!toVertexMap.containsKey(object2))
		{
			throw std::runtime_error("删除不存在的边");
			return;
		}
		DbListNode<Edge>* enode1 = toEdgeMap.getValue(std::make_pair(object1, object2));
		DbListNode<Vertex>* node1 = enode1->data.vertex;
		enode1->data.clear();
		node1->data.edges->Remove(enode1);
		EdgeCount--;
		toEdgeMap.Remove(std::make_pair(object1, object2));
		toEdgeMap.Remove(std::make_pair(object2, object1));
	}
	bool isEdge(Object object1, Object object2)
	{
		return toEdgeMap.containsKey(std::make_pair(object1, object2));
	}
	Object* getVertices()
	{
		Object* array=new Object[VertexCount];
		DbListNode<Vertex>* node = vertexs->begin();
		for (int i=0; node != vertexs->Head(); i++)
		{
			Object object = toObjectMap.getValue(node->data.data);
			array[i] = object;
			node = node->rlink;
		}
		return array;
	}
	
	int Degree(Object object)
	{
		DbListNode<Vertex>* node = toVertexMap.getValue(object);
		return node->data.degree;
	}
	Weight getWeight(Object object1, Object object2)
	{
		if (!toVertexMap.containsKey(object1) || !toVertexMap.containsKey(object2))
		{
			throw std::runtime_error("有不存在的顶点");
		}
		DbListNode<Edge>* node = toEdgeMap.getValue(std::make_pair(object1, object2));
		return node->data.weight;
	}
};