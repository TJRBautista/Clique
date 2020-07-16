#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
//#include "Graph.h"
//#include "structures.h"

void init();
int findNewCluster(int node);
void changeCluster (int node, int clusterID);
bool removeNode(int node, int clusterID);
bool addNode(int node, int clusterID);
double changeMod_out (int i, const int srcID);
double changeMod_in (int i, const int destID);
void cleanLouvain(int numClusters, int numNodes);

int *clusterMap;
Cluster **clusterSet;
Graph *OG;
Graph *curG;
double m;

void louvain (Graph * const G) {
	//bool changedCluster;
	OG = G;
	curG = copyGraph(G);
	
	do {
		//changedCluster = false;
		init();
		displayClusterSet(clusterSet, curG->numNodes);
		
		for (int curNode = 0; curNode < curG->numNodes; curNode++) {
			int newClusterID = findNewCluster(curNode);
			
			//if (newClusterID != -1)
				//changedCluster = true;
			
			bool isAdded = false;
			isAdded = addNode(curNode, newClusterID);
			assert(isAdded);
		}
	} while (false);
	
	displayClusterSet(clusterSet, curG->numNodes);
	cleanLouvain(curG->numNodes, curG->numNodes);
	destroyGraph(curG);
}

void init() {
	clusterSet = malloc(curG->numNodes * sizeof *clusterSet);
	clusterMap = malloc(curG->numNodes * sizeof *clusterMap);
	m = 0.0;
	
	for (int curNode = 0; curNode < curG->numNodes; curNode++) {
		clusterSet[curNode] = malloc(sizeof *clusterSet[curNode]);
		clusterSet[curNode]->indices = malloc(sizeof *clusterSet[curNode]->indices);
		clusterSet[curNode]->indices[0] = curNode;
		clusterSet[curNode]->numNodes = 1;
		clusterSet[curNode]->sigmaTot = sum(curG->adjMat[curNode], curG->numNodes);
		
		clusterMap[curNode] = curNode;
		m += sum(curG->adjMat[curNode], curG->numNodes);
	}
}

int findNewCluster(int node) {
	int newCluster = -1;
	bool isRemoved = false;
	isRemoved = removeNode(node, clusterMap[node]);
	assert(isRemoved);
	
	double dQ_out = changeMod_out(node, clusterMap[node]);
	double dQ_in_greatest = dQ_out;
	
	
	for (int neighbour = 0; neighbour < curG->numNodes; neighbour++) {
		if (curG->adjMat[node][neighbour] != 0) {
			double dQ_in = changeMod_in(node, clusterMap[neighbour]);
			
			if (dQ_in > dQ_in_greatest) {
				dQ_in_greatest = dQ_in;
				newCluster = clusterMap[neighbour];
			}
		}
	}
	
	return newCluster;
}

void changeCluster (int node, int clusterID) {
	bool isRemoved = false;
	bool isAdded = false;
	
	isRemoved = removeNode(node, clusterMap[node]);
	assert(isRemoved);
	isAdded = addNode(node, clusterID);
	assert(isAdded);
	clusterMap[node] = clusterID;
}

bool removeNode(int node, int clusterID) {
	bool removed = false;
	Cluster *C = clusterSet[clusterID];
	for (int curNode = 0; curNode < C->numNodes && !removed; curNode++) {
		if (C->indices[curNode] == node) {
			for(int i = curNode; i < C->numNodes - 1; i++)
				C->indices[i] = C->indices[i+1];
			
			int *temp;
			C->numNodes--;
			do {
				temp = realloc(C->indices, C->numNodes * sizeof *(C->indices));
			} while (NULL == temp);
			
			C->sigmaTot -= sum(curG->adjMat[node], curG->numNodes);
			
			removed = true;
		}
	}
	clusterMap[node] = -1;
	return(removed);
}

bool addNode(int node, int clusterID) {
	Cluster *C = clusterSet[clusterID];
	int *temp;
	
	C->numNodes++;
	do {
		temp = realloc(C->indices, C->numNodes * sizeof *(C->indices));
	} while (NULL == temp);
	
	C->indices[C->numNodes - 1] = node;
	C->sigmaTot += sum(curG->adjMat[node], curG->numNodes);
	clusterMap[node] = clusterID;
	
	return true;
}

double changeMod_out (int i, const int srcID) {
	double k = 0;
	double k_in = 0;
	double result;
	
	if (srcID == -1)
		result = 0;
	else {
		for (int curNode = 0; curNode < curG->numNodes; curNode++) {
			k += curG->adjMat[i][curNode];
			
			if (clusterMap[curNode] == srcID) {
				k_in += curG->adjMat[i][curNode];
				k_in += curG->adjMat[curNode][i];
			}
		}
		
		result = ((k * clusterSet[srcID]->sigmaTot / m) - k_in) / (2*m);
	}
	
	assert(result >= -2 && result <= 2);
	return result;
}

double changeMod_in (int i, const int destID) {
	double k = 0;
	double k_in = 0;
	double result;
	
	for (int curNode = 0; curNode < curG->numNodes; curNode++) {
		k += curG->adjMat[i][curNode];
		
		if (clusterMap[curNode] == destID && curNode != i) {
			k_in += curG->adjMat[i][curNode];
			k_in += curG->adjMat[curNode][i];
		}
	}
	
	result = (k_in - (k * clusterSet[destID]->sigmaTot / m)) / (2*m);
	assert(result >= -2 && result <= 2);
	return result;
}

void cleanLouvain(int numClusters, int numNodes) {
	for(int curCluster = 0; curCluster < numClusters; curCluster++) {
		free(clusterSet[curCluster]);
	}
	free(clusterSet);
	free(clusterMap);
}