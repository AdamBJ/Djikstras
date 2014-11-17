#ifndef HEAP_H_
#define HEAP_H_
#include <vector>;

struct	HeapEntry {
	HeapEntry(int a, int b){
		id = a;
		key = b;
	}
	int id;
	int key;
};

struct	Edge {
	Edge(int a, int b){
		id = a;
		cost = b;
	}
	int id;
	int cost;
};

class Heap{
	public:	
		Heap(int finalSize);
		~Heap();
		void Insert(HeapEntry e);
		void InitializeForDjikstras();
		HeapEntry Delete(int id);
		HeapEntry Delete_Min();
		int Size();
		HeapEntry Get_Node(int id);
		int Get_Rear();
	private:
		//bubble up/down
		void Swap(HeapEntry& a, HeapEntry& b);
		//this function helps maintain data hiding. Delete_Min is just repeated calls to this recursive method, but the
		//user shouldn't have to pass anything to delete min, so Delete_Min(). Hide the implementation!
		void Bubble_Down_Recursivley(int parentIndex);
		//index past the final entry. Where new insert will put an element in the array.
		int rear;
		std::vector<HeapEntry> heap;

};

#endif