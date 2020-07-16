typedef struct cluster {
	int* indices;
	int numNodes;
	double sigmaTot;
} Cluster;

typedef struct cascade {
	int* indices;
	double* activationTimes;
	int numNodes;
} Cascade;

void displayCascade (Cascade * const C);
void displayClusterSet (Cluster ** const set, const int numClusters);
void displayCluster (Cluster * const C);