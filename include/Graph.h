typedef struct graph {
	double** adjMat;
	int numNodes;
} Graph;

Graph *createEmptyGraph (const int numNodes);
void destroyGraph (Graph * const G);
void addGraphs (Graph * const A, Graph * const B);
double sum (double * const list, const int size);
void displayGraph (Graph * const G);
Graph *copyGraph(Graph * const G);