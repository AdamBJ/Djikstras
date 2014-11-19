#include "Heap.h"
#include <sstream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

void ReadFile(std::vector<Edge> adjList[], std::string fileName);
const int NUM_VERTICES = 200;
const int START_VERTEX = 29;

int main(){
	//valid entries in adjList start from[1] so that vertex #1 is stored in [1].
	std::vector<Edge> adjList[NUM_VERTICES + 1];
	std::vector<int> shortestPaths(NUM_VERTICES + 1);
	std::vector<std::string> pathFromStartToVertex(NUM_VERTICES + 1);
	std::vector<std::string> popOrder;
	std::vector<std::string> popScore;
	ReadFile(adjList, "dijkstraData.txt");
	//ReadFile(adjList, "test.txt");
	Heap heap(NUM_VERTICES);
	heap.InitializeForDjikstras(); 

	HeapEntry min(0, 0);

	//for each of the remaining vertices, process using Djikstra's greedy selection rule
	for (int i = 0; i < NUM_VERTICES; i++){
		
		if (i == 0){
			min = heap.Delete_Min();
			std::stringstream ss;
			ss << START_VERTEX;
			pathFromStartToVertex[START_VERTEX] = ss.str();
			popOrder.push_back(ss.str());
			popScore.push_back("0");
		}
		if (i != 0){
			min = heap.Delete_Min();
			std::stringstream ss;
			ss << " " << min.id;
			popOrder[0] += (ss.str());
			std::stringstream st;
			st << " " << min.key;
			popScore[0] += st.str();

		}

		shortestPaths[min.id] = min.key;

		//recalculate keys of any nodes that now have edges crossing the boundary between X(processed) and V-X(unprocessed)
		for (int q = 0; q < adjList[min.id].size(); q++){
			int headID = adjList[min.id][q].id;
			int costToHead = adjList[min.id][q].cost;
			HeapEntry head = heap.Delete(headID);
			
			if (head.key > shortestPaths[min.id] + costToHead) {
				head.key = shortestPaths[min.id] + costToHead;
				
				std::stringstream ss;
				ss << pathFromStartToVertex[min.id] << " " << head.id;
				pathFromStartToVertex[head.id] = ss.str();	
			}
			if (head.id!=-1) heap.Insert(head);
		}
	}

	//std::ofstream outf("heaprslt.txt");
	//outf << shortestPaths[7] << "," << shortestPaths[37] << "," << shortestPaths[59] << "," << shortestPaths[82];
	//outf << "," << shortestPaths[99] << "," << shortestPaths[115] << "," << shortestPaths[133];
	//outf << "," << shortestPaths[165] << "," << shortestPaths[188] << "," << shortestPaths[197];

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