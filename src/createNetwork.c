#include <math.h>
#include <stdlib.h>
#include "Graph.h"
#include "structures.h"

void normalise (Graph *G);

Graph *createNetwork (Cascade ** const cascades, const int numCascades, const int numNodes, const double a) {
	Graph *G = createEmptyGraph(numNodes);

	for (int cascadeIndex = 0; cascadeIndex < numCascades; cascadeIndex++) {
		Graph *tempG = createEmptyGraph(numNodes);
		Cascade *curCascade = cascades[cascadeIndex];
		displayCascade(curCascade);
		
		for (int i = 0; i < curCascade->numNodes; i++) {
			for (int j = 0; j < curCascade->numNodes; j++) {
				double delta = curCascade->activationTimes[i] - curCascade-> activationTimes[j];
				if (delta > 0) { // j infects i
					int index_i = curCascade->indices[i];
					int index_j = curCascade->indices[j];
					tempG->adjMat[index_i][index_j] += exp(-a * delta);
				}
			}
		}
		
		normalise(tempG);
		displayGraph(tempG);
		addGraphs(G, tempG);
		displayGraph(G);
		destroyGraph(tempG);
	}
	
	for (int i = 0; i < G->numNodes; i++) {
		for (int j = i+1; j < G->numNodes; j++) {
			G->adjMat[i][j] += G->adjMat[j][i];
			G->adjMat[j][i] = G->adjMat[i][j];
		}
	}
	
	return G;
}

void normalise (Graph *G) {
	for(int curRow = 0; curRow < G->numNodes; curRow++) {
		double totalWeight = sum(G->adjMat[curRow], G->numNodes);
		if (totalWeight != 0) {
			for (int i = 0; i < G->numNodes; i++)
				G->adjMat[curRow][i] /= totalWeight;
		}
	}
}