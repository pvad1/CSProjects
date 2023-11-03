
#ifndef GRAPH_H
#define GRAPH_H

// Defines a graph.
class Graph {
public:
	// Constructors/Destructor for Graph.
	Graph();
	~Graph();

	// Loads the graph.
	void LoadGraph(const char *graphFileName);

	// Runs Dijkstra's algorithm, using the specified vertex as the starting vertex.
	void RunDijkstra(char startVertex);

	// Returns the distance of the vertex with the specified name from the starting vertex.
	int GetDistance(char vertex);

	// Returns the number of updates made to the vertex's distance during the last call of RunDijkstra.
	int GetNumberOfUpdates(char vertex);

	void AddVertex(char name);

	void AddEdge(char src, char dest, int weight);

	int GetVertexDistance(char vertexName);
	
	void printMatrix();

};

#endif