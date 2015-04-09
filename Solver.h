#pragma once
#include <stack>

enum MD_STATE { eDISCOVERED, eFRONTIER, eEXPLORED };

struct SolverMetaData
{
	MD_STATE state;
	SolverMetaData() : state(eDISCOVERED){}
};

class Solver
{
	SolverMetaData *m_md;
	std::stack<unsigned> frontier;
	float **e_adjacencyMatrix;
	unsigned m_nNodes;
	unsigned m_start, m_goal;

	Solver(unsigned a_nNodes, float **am) : m_nNodes(a_nNodes), e_adjacencyMatrix(am), m_md(new SolverMetaData[m_nNodes])
	{}

	void path(unsigned a_start, unsigned a_goal)
	{	
		m_start = a_start;
		m_goal = a_goal;

		memset(m_md, 0, sizeof(SolverMetaData)*m_nNodes);
		frontier.push(m_start);
	}

	SolverMetaData get_md();

	bool step()
	{
		unsigned current = frontier.top();
		frontier.pop();
		if (current == m_goal) return true;
		m_md[current].state = eEXPLORED;

		for (int i = 0; i < m_nNodes; ++i)
		{
			if (e_adjacencyMatrix[current][i] > 0 && m_md[i].state == eDISCOVERED)
			{
				m_md[i].state = eFRONTIER;
				frontier.push(i);
			}
		}
		return false;
	}
};