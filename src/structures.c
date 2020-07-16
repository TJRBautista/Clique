#include <stdio.h>
#include "structures.h"

void displayCascade (Cascade * const C) {
	printf("Number of nodes: %d\n", C->numNodes);
	for(int i = 0; i < C->numNodes; i++) {
		printf("%d - %f\n", C->indices[i], C->activationTimes[i]);
	}
	printf("\n");
}

void displayClusterSet (Cluster ** const set, int numClusters) {
	for (int i = 0; i < numClusters; i++) {
		printf("%d: ", i);
		displayCluster(set[i]);
	}
	printf("\n");
}

void displayCluster (Cluster * const C) {
	for (int i = 0; i < C->numNodes; i++)
		printf("%d ", C->indices[i]);
	printf("\n");
}