#include "Heap.h"
#include <sstream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

void ReadFile(std::vector<Edge> adjList[], std::string fileName);
const int NUM_VERTICES = 4;
int main(){
	//valid entries in adjList start from[1], not zero, so that vertex #1 is stored in [1].
	std::vector<Edge> adjList[NUM_VERTICES + 1];
	std::vector<int> shortestPaths(NUM_VERTICES + 1);
	std::vector<std::string> pathFromStartToVertex(NUM_VERTICES + 1);
	//ReadFile(adjList, "dijkstraData.txt");
	ReadFile(adjList, "test.txt");
	Heap heap(NUM_VERTICES);
	heap.InitializeForDjikstras(); 

	HeapEntry min(0, 0);

	//for each of the remaining vertices, process using Djikstra's greedy selection rule
	for (int i = 0; i < NUM_VERTICES; i++){
		HeapEntry p(0, 0);
		p = heap.Get_Node(4);
		min = heap.Delete_Min();
		pathFromStartToVertex[0] += min.id;
		pathFromStartToVertex[min.id] = pathFromStartToVertex[0];
		cvzxc
		for (int i = 0; i < adjList[min.id].size(); i++){
			if (adjList[min.id][i].id == 4) std::cout << "4 adjacent to vertex " << min.id << '\n';
		}

		shortestPaths[min.id] = min.key;
		//recalculate keys of any nodes that now have edges cross the boundary between X(processed) and V-X(unprocessed)
		for (int q = 0; q < adjList[min.id].size(); q++){
			int headID = adjList[min.id][q].id;
			int costToHead = adjList[min.id][q].cost;
			HeapEntry head = heap.Delete(headID);
			if (head.id != -1){//if delete was successful
				if (head.key > shortestPaths[min.id] + costToHead) {
					head.key = shortestPaths[min.id] + costToHead;
				}
				heap.Insert(head);
			}
		}
	}
	//std::cout << shortestPaths[7] << "," << shortestPaths[37] << "," << shortestPaths[59] << "," << shortestPaths[82];
	//std::cout << "," << shortestPaths[99] << "," << shortestPaths[115] << "," << shortestPaths[133];
	//std::cout << "," << shortestPaths[165] << "," << shortestPaths[188] << "," << shortestPaths[197];
	return 0;
}

void ReadFile(std::vector<Edge> adjList[], std::string fileName){
	std::ifstream adjList_txt(fileName);
	std::string line, token;
	int id, cost, head;

	if (!adjList_txt.is_open()) {
		std::cout << "Failed to open file.";
	}
	else {
		while (std::getline(adjList_txt, line))
		{
			std::istringstream iss(line);
			iss >> id;
			while (iss >> token){
				std::istringstream tokenizer(token);
				tokenizer >> head;
				if (tokenizer.peek() == ',')
					tokenizer.ignore();
				tokenizer >> cost;
				Edge node(head, cost);
				adjList[id].push_back(node);
			}
		}
		adjList_txt.close();
	}
}