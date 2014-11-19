#include "Heap.h";
#include <exception>;
#include <iostream>

//int main() {
//	Heap test = Heap();
//	
//	int id, key;
//	char op;
//	
//	while (true){
//		std::cin >> op >> id >> key;
//
//		if (op == 'i'){
//			test.Insert(HeapEntry(id, key));
//		}
//		else if (op == 'd'){
//			test.Delete(id, key);
//		}
//		else if (op == 'm'){
//			test.Delete_Min();
//		}
//
//		for (int i = 0; i < 5; i++){
//			std::cout << '\t';
//		}
//		std::cout << test.Get_Node(0).id << "(" << test.Get_Node(0).key << ")" << '\n';
//		for (int i = 1; i < 5; i++){
//			std::cout << '\t';
//		}
//
//		int inLevelCounter = 0;
//		int levelMax = 2;
//		HeapEntry temp(1, 2);
//		for (int i = 1; i < test.Get_Rear(); i++){
//			temp = test.Get_Node(i);
//			std::cout << temp.id << "(" << temp.key << ")" << '\t';
//			inLevelCounter++;
//			if (inLevelCounter == levelMax){
//				std::cout << '\n';
//				levelMax *= 2;
//				for (int i = levelMax / 2; i < 5; i++){
//					std::cout << '\t';
//				}
//				inLevelCounter = 0;
//			}
//		}
//	}
//	return 0;
//}


Heap::Heap(int finalSize){
	rear = 0;
	heap.reserve(finalSize);
}

Heap::~Heap(){

}

void Heap::InitializeForDjikstras(){
	int numberVertices = heap.capacity();
	HeapEntry t(1, 0);
	heap.push_back(t);
	for (int i = 1; i <= numberVertices; i++){
		//insert all but the first node with a key of "+infinity"
		HeapEntry t(i, 1000000);
		heap.push_back(t);
	}
	//start test
	/*HeapEntry q(1, 999999);
	heap[28] = q;
	HeapEntry r(29, 0);
	heap[0] = r;*/
	//end test

	rear = numberVertices;
}

int Heap::Get_Rear(){
	return rear;
}

int Heap::Size(){
	return heap.size();
}

HeapEntry Heap::Get_Node(int id){
	for (int i = 0; i < rear; i++){
		if (heap[i].id == id) return heap[i];
	}
	HeapEntry fail(-1, -1);
	return fail;
}

void Heap::Insert(HeapEntry e){
	
	for (int i = 0; i < rear; i++){
		if (heap[i].id == e.id){
			std::cout << "Duplicate id detected. Insert failed."; 
			goto end;
		}
	}

	if (rear < heap.size()) heap[rear] = e;
	else heap.push_back(e);

	rear++;

	int childIndex = rear - 1;
	int parentIndex;
	//-1 because we start our heap from [0], not 1. Draw a tree, insert and bubble up to see why neccesary.
	if (childIndex%2==0) parentIndex = childIndex/2 - 1;
	else parentIndex = childIndex / 2 - 1 + 1;//need to make adjustment if childIndex is odd. Consider case where childIndex==1. 1 / 2 - 1 ==-1, not zero.
	if (parentIndex < 0) return;//if we've gone past the root, as will happen if we've just swapped into the root, brea
	
	while (heap[childIndex].key < heap[parentIndex].key){
		Swap(heap[childIndex], heap[parentIndex]);
		childIndex = parentIndex;
		
		if (childIndex % 2 == 0) parentIndex = childIndex / 2 - 1;
		else parentIndex = childIndex / 2 - 1 + 1;

		if (parentIndex < 0) break;//if we've gone past the root, as will happen if we've just swapped into the root, break.
	}
	//reset rear so that it once again points to the last element in the heap

	end:;
}

HeapEntry Heap::Delete(int id){
	int index = -1;
	//attempt to find the entry e, asumming the heap isnt empty. It will be empty when we delete the final node. The final node deletion will still trigger updates, which we have to ignore.
	if (rear != 0){
		for (int i = 0; i < rear; i++){
			if (heap[i].id == id) index = i;
		}

		if (index == -1){//not found in the heap
			HeapEntry t(-1, -1);
			return t;
		}

		Swap(heap[index], heap[rear - 1]);
		rear--;
		int parentIndex = index;

		//check both child of newly place node, do we need to bubble down?
		for (int i = 0; i < 2; i++){
			int childIndex = parentIndex * 2 + i + 1;
			//why parent * 2 + i + 1? Because the 2*i formula for child is predicated on the first entry in the heap being at [1]. Ours is at [0]  so we have to adjust.
			if (childIndex < rear){
				if (heap[parentIndex].key > heap[childIndex].key){
					Swap(heap[parentIndex], heap[childIndex]);
					parentIndex = childIndex;
				}
			}
		}

		return heap[rear];
	}
	//the heap was already empty
	HeapEntry t(-1, -1);
	return t;
}

HeapEntry Heap::Delete_Min(){
	Swap(heap[rear-1], heap[0]);
	rear--;
	int parentIndex = 0;

	//check both child of newly place node, do we need to bubble down?
	for (int i = 0; i < 2; i++){
		int childIndex = parentIndex * 2 + i + 1;
		//why parent * 2 + i + 1? Because the 2*i formula for child is predicated on the first entry in the heap being at [1]. Ours is at [0]  so we have to adjust.
		if (childIndex < rear){
			if (heap[parentIndex].key > heap[childIndex].key){
				Swap(heap[parentIndex], heap[childIndex]);
				//RECURSE
				Bubble_Down_Recursivley(childIndex);
				
			}
		}
	}

	return heap[rear];
}

void Heap::Bubble_Down_Recursivley(int parentIndex){
	

	//check both child of newly place node, do we need to bubble down?
	for (int i = 0; i < 2; i++){
		int childIndex = parentIndex * 2 + i + 1;
		//why parent * 2 + i + 1? Because the 2*i formula for child is predicated on the first entry in the heap being at [1]. Ours is at [0]  so we have to adjust.
		if (childIndex < rear){//this is the de-facto basecase
			if (heap[parentIndex].key > heap[childIndex].key){
				Swap(heap[parentIndex], heap[childIndex]);
				//RECURSE
				Bubble_Down_Recursivley(childIndex);

			}
		}
	}

}

void Heap::Swap(HeapEntry& a, HeapEntry& b){
	HeapEntry temp = a;
	a = b;
	b = temp;
}