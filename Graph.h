#pragma once
#include "dep/cmathutils.h"
#include <vector>

class Graph
{
	vec2   *m_positions;		// node Positions
	int     m_nNodes;			// number of nodes
	int		m_maxNodes;			// Maxium number of nodes
	float **m_adjacencyMatrix;	// edges

public:
	const vec2   *getPostitions() const;
	float  **getAdjacencyMatrix() const;
	const     unsigned int size() const;

	Graph(int a_nNodes);
	~Graph();

	int  addNode(const vec2 &pos);
	bool setEdge(unsigned int nid1, unsigned int nid2, float weight = 1);
	int  findNode(const vec2 &pos);
};