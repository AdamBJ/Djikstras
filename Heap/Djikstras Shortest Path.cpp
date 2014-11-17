#include "Heap.h"
#include <sstream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <sstream>

void ReadFile(std::vector<Edge> adjList[], std::string fileName);
bool Found_In_VX(int vertexID, const std::vector<int>& X);
const int NUM_VERTICES = 4;
const int START_VERTEX = 1;
int main(){
	//valid entries in adjList start from[1], not zero, so that vertex #1 is stored in [1].
	std::vector<Edge> adjList[NUM_VERTICES + 1];
	std::vector<int> shortestPaths(NUM_VERTICES + 1);
	std::vector<int> X;
	std::vector<std::string> pathFromStartToVertex(NUM_VERTICES + 1);
	//ReadFile(adjList, "dijkstraData.txt");
	ReadFile(adjList, "test.txt");
	
	X.push_back(START_VERTEX);
	shortestPaths[START_VERTEX] = 0;
	pathFromStartToVertex[START_VERTEX] = START_VERTEX;
	
	//for each of the remaining vertices, process using Djikstra's greedy selection rule
	for (int i = 0; i < NUM_VERTICES; i++){
		//scan all edges protruding from the vertices in X
		std::vector<Edge> crossEdges;
		std::vector<int> crossEdgeTails;
		for (int i = 0; i <X.size(); i++){

			//If we find an edge with its head in V-X (V-X = unprocessed vectors. To determine if head is in X-Y, search X for the head.
			//If not in X, it is in X-Y.
			for (int q = 0; q < adjList[X[i]].size(); q++){

				//record greedy score for edges that meet our criteria for as we find them
				int head = adjList[X[i]][q].id;
				if (Found_In_VX(head, X)){
					adjList[X[i]][q].cost += shortestPaths[X[i]];
					crossEdges.push_back(adjList[X[i]][q]);
					crossEdgeTails.push_back(X[i]);
				}

			}

			//of the edges we've just found, determine the one with the smallest greedy score. Add its head to X (set S[vert we just added]= GC).
			Edge smallest=crossEdges[0];
			int tail;
			for (int k = 1; k < crossEdges.size(); k++){
				if (smallest.cost> crossEdges[k].cost) smallest = crossEdges[k];
				tail = k;
			}

			//record the path we used to get to the vertex we just added to X (B[vert we just added] = B[edge tail] + head.

			std::stringstream ss;
			ss << pathFromStartToVertex[crossEdgeTails[tail]] << smallest.id;
			
			X.push_back(smallest.id);
			shortestPaths[smallest.id] = smallest.cost;
			pathFromStartToVertex[smallest.id] = ss.str();
		}
	}
	//std::cout << shortestPaths[7] << "," << shortestPaths[37] << "," << shortestPaths[59] << "," << shortestPaths[82];
	//std::cout << "," << shortestPaths[99] << "," << shortestPaths[115] << "," << shortestPaths[133];
	//std::cout << "," << shortestPaths[165] << "," << shortestPaths[188] << "," << shortestPaths[197];
	return 0;
}

//if the vertex is in X its not in V-X. Pass by reference cause it's faster than pass by value. const cause we want to show we won't change it.
bool Found_In_VX(int vertexID, const std::vector<int>& X){
	for (int i = 0; i < X.size(); i++){
		if (X[i] == vertexID) return false;
	}
	return true;
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