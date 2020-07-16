#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"

Graph *createEmptyGraph (const int numNodes) {
	double **adjMat = malloc(numNodes * sizeof *adjMat);
	Graph *G = malloc(sizeof *G);
	
	for (int i = 0; i < numNodes; i++) {
		adjMat[i] = malloc(numNodes * sizeof *adjMat[i]);
		for (int j = 0; j < numNodes; j++)
			adjMat[i][j] = 0;
	}
	
	G->adjMat = adjMat;
	G->numNodes = numNodes;
	
	return G;
}

void destroyGraph (Graph * const G) {
	for(int i = 0; i < G->numNodes; i++) {
		free(G->adjMat[i]);
	}
	free(G->adjMat);
	free(G);
}

void addGraphs (Graph * const A, Graph * const B) {
	assert(A->numNodes == B->numNodes);
	for (int curRow = 0; curRow < A->numNodes; curRow++) {
		for (int curCol = 0; curCol < A->numNodes; curCol++) {
			A->adjMat[curRow][curCol] += B->adjMat[curRow][curCol];
		}
	}
}

double sum (double * const list, const int size) {
	double result = 0;
	
	for(int i = 0; i < size; i++) {
		result += list[i];
	}
	
	return result;
}

void displayGraph(Graph * const G) {
	for (int curRow = 0; curRow < G->numNodes; curRow++) {
		for (int curCol = 0; curCol < G->numNodes; curCol++)
			printf("%f ", G->adjMat[curRow][curCol]);
		printf("\n");
	}
	printf("\n");
}

Graph *copyGraph (Graph * const G) {
	Graph *copy = createEmptyGraph(G->numNodes);
	
	for(int curRow = 0; curRow < copy->numNodes; curRow++) 
		for(int curCol = 0; curCol < copy->numNodes; curCol++)
			copy->adjMat[curRow][curCol] = G->adjMat[curRow][curCol];
		
	copy->numNodes = G->numNodes;
	
	return copy;
}