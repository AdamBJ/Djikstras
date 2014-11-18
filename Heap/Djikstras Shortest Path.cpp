#include "Heap.h"
#include <sstream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <sstream>

void ReadFile(std::vector<Edge> adjList[], std::string fileName);
bool Found_In_VX(int vertexID, const std::vector<int>& X);
const int NUM_VERTICES = 200;
const int START_VERTEX = 29;
int main(){
	//valid entries in adjList start from[1], not zero, so that vertex #1 is stored in [1].
	std::vector<Edge> adjList[NUM_VERTICES + 1];
	std::vector<int> shortestPaths(NUM_VERTICES + 1, 1000000);
	std::vector<std::string> popOrder;
	std::vector<int> X;
	std::vector<std::string> pathFromStartToVertex(NUM_VERTICES + 1);
	ReadFile(adjList, "dijkstraData.txt");
	//ReadFile(adjList, "test.txt");
	
	X.push_back(START_VERTEX);
	shortestPaths[START_VERTEX] = 0;
	std::stringstream ss;
	ss << START_VERTEX;
	pathFromStartToVertex[START_VERTEX] = ss.str();
	popOrder.push_back(ss.str());
	
	//for each of the remaining vertices, process using Djikstra's greedy selection rule
	for (int p = 1; p < NUM_VERTICES; p++){
		//scan all edges protruding from the vertices in X
		std::vector<Edge> crossEdges;
		
		int sizeX = X.size();//need this variable. If we say until i<X.size() we'll run more or less than we want since we resize X within the for loop.
		for (int t = 0; t < sizeX; t++){
			//If we find an edge with its head in V-X (V-X = unprocessed vectors. To determine if head is in X-Y, search X for the head.
			//If not in X, it is in X-Y.
			for (int q = 0; q < adjList[X[t]].size(); q++){
				//record greedy score for edges that meet our criteria for as we find them
				int head = adjList[X[t]][q].id;
				//if head is in VX and the previous cost to head is > the shortest path to X[t] + the edge from X[t] to head, update the path
				if (Found_In_VX(head, X)){
					if (shortestPaths[head] > shortestPaths[X[t]] + adjList[X[t]][q].cost){
						shortestPaths[head] = shortestPaths[X[t]] + adjList[X[t]][q].cost;//our current best guess
					}
					Edge crossEdge(head, shortestPaths[head]);
					crossEdges.push_back(crossEdge);

					//record the path we used to get to the vertex we just reached (B[vert we've reached] = B[edge tail] + head.
					std::stringstream ss;
					ss << pathFromStartToVertex[X[t]] << " " << head;
					pathFromStartToVertex[head] = ss.str();
				}
			}
		}
		//of the edges we've just found, determine the one with the smallest greedy score. Add its head to X (set S[vert we just added]= GC).
		if (crossEdges.size() != 0){
			Edge smallest = crossEdges[0];
			for (int k = 1; k < crossEdges.size(); k++){
				if (smallest.cost > crossEdges[k].cost){
					smallest = crossEdges[k];
				}
			}
			X.push_back(smallest.id);
			std::stringstream ss;
			ss << " " << smallest.id;
			popOrder[0] += (ss.str());
		}
	}

	std::ofstream outf("rslts.txt");
	outf << shortestPaths[7] << "," << shortestPaths[37] << "," << shortestPaths[59] << "," << shortestPaths[82];
	outf << "," << shortestPaths[99] << "," << shortestPaths[115] << "," << shortestPaths[133];
	outf << "," << shortestPaths[165] << "," << shortestPaths[188] << "," << shortestPaths[197];
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