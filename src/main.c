#include <stdio.h>
#include <stdlib.h>
//#include "Graph.h"
//#include "structures.h"
#include "createNetwork.c"
#include "louvain.c"

#define testSize 9
double testA[testSize][testSize] = {
	{0, 1, 1, 0, 0, 0, 0, 0, 0},
	{1, 0, 1, 0, 0, 0, 0, 0, 0},
	{1, 1, 0, 1, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 0, 0, 1, 0, 1},
	{0, 0, 0, 0, 0, 1, 1, 1, 0}};

Cascade **genTestCascades ();
Graph *genTestGraph();
void cleanMain(Cascade **cascades);

int main (int argc, char *argv[]) {
	Cascade **cascades = genTestCascades();
	
	Graph *G = createNetwork(cascades, 2, 4, 0);
	displayGraph(G);
	destroyGraph(G);
	
	G = genTestGraph();
	louvain(G);
	destroyGraph(G);
	
	cleanMain(cascades);
}

Cascade **genTestCascades () {
	Cascade **cascades = malloc(2 * sizeof *cascades);
	
	Cascade *c1 = malloc(sizeof *c1);
	c1->numNodes = 4;
	c1->indices = malloc(c1->numNodes * sizeof *(c1->indices));
	c1->activationTimes = malloc(c1->numNodes * sizeof *(c1->activationTimes));
	c1->indices[0] = 0;
	c1->indices[1] = 1;
	c1->indices[2] = 2;
	c1->indices[3] = 3;
	c1->activationTimes[0] = 1.0;
	c1->activationTimes[1] = 2.0;
	c1->activationTimes[2] = 2.0;
	c1->activationTimes[3] = 2.0;
	
	Cascade *c2 = malloc(sizeof *c2);
	c2->numNodes = 4;
	c2->indices = malloc(c2->numNodes * sizeof *(c2->indices));
	c2->activationTimes = malloc(c2->numNodes * sizeof *(c2->activationTimes));
	c2->indices[0] = 0;
	c2->indices[1] = 1;
	c2->indices[2] = 2;
	c2->indices[3] = 3;
	c2->activationTimes[0] = 1.0;
	c2->activationTimes[1] = 1.0;
	c2->activationTimes[2] = 1.0;
	c2->activationTimes[3] = 2.0;
	
	cascades[0] = c1;
	cascades[1] = c2;
	
	return cascades;
}

Graph *genTestGraph() {
	Graph *G = createEmptyGraph(testSize);
	for (int i = 0; i < testSize; i++)
		for (int j = 0; j < testSize; j++)
			G->adjMat[i][j] = testA[i][j];
	return G;
}

void cleanMain(Cascade **cascades) {
	for(int i = 0; i < 2; i++) {
		free((cascades[i])->indices);
		free((cascades[i])->activationTimes);
		free(cascades[i]);
	}
	
	free(cascades);
}