#include "Graph.h"


const vec2 *Graph::getPostitions()   const{ return m_positions; }
float **Graph::getAdjacencyMatrix()  const{ return m_adjacencyMatrix; }
const unsigned int Graph::size()	 const{ return m_nNodes; }

/// Constructor  /////////////////////////////////////////////////////
Graph::Graph(int a_nNodes) : m_maxNodes(a_nNodes), m_nNodes(0),
		m_positions(new vec2[m_maxNodes]), m_adjacencyMatrix(new float *[m_maxNodes])
{
	for (int i = 0; i < m_maxNodes; ++i)
	{
		m_adjacencyMatrix[i] = new float[m_maxNodes];
		memset(m_adjacencyMatrix[i], 0, 4 * m_maxNodes);
	}
	memset(m_positions, 0, sizeof(vec2)* m_maxNodes);
}
/// Deconstructor  ///////////////////////////////////////////////////
Graph::~Graph()
{
	for (int i = 0; i < m_maxNodes; ++i)
		delete[] m_adjacencyMatrix[i];
	delete[] m_adjacencyMatrix;
	delete[] m_positions;
}
/// Add Node to Graph  ///////////////////////////////////////////////
int  Graph::addNode(const vec2 &pos)
{
	if (m_nNodes == m_maxNodes)
		return -1;

	m_positions[m_nNodes] = pos;
	m_nNodes++;
	return m_nNodes - 1;
}
/// Set Edge between Nodes  //////////////////////////////////////////
bool Graph::setEdge(unsigned int nid1, unsigned int nid2, float weight)
{
	if (nid1 >= m_nNodes || nid2 >= m_nNodes || weight < 0)
		return false;
	m_adjacencyMatrix[nid1][nid2] = weight;
	m_adjacencyMatrix[nid2][nid1] = weight;
	return true;
}
/// Find Closest Node to Position  ///////////////////////////////////
int  Graph::findNode(const vec2 &pos)
{
	float d;
	for (int i = 0; i < m_maxNodes; ++i)
	{
		if (i == 0)
			d = distance(pos, m_positions[i]);
		else
		{
			auto a = distance(pos, m_positions[i]);
			if (a <= d)
				d = a;
		}
	}
	return d;
}
//////////////////////////////////////////////////////////////////////