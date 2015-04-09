#include "dep\shapes.h"
#include <iostream>
#include "Graph.h"
#include <cassert>

void main()
{

	mul   (mat4::rotate2D(PI/4), vec2(12, 0)) == vec2(0, 12);
	mulaff(mat4::translate2D(vec2(12, 0)), vec2(12, 0)) == vec2(24, 0);

	auto w = openContext();	//defualt 640 x 480
	auto m = mat4::ortho(0, 640, 0, 480, 0, 100);

	//aabb a(vec2(40, 40), vec2(40, 60));
	//aabb b(vec2(20, 60), vec2(20, 40));

	//circle c(vec2(100, 100), 180);
	
	Graph g(5);

	g.addNode(vec2(200, 320));
	g.addNode(vec2(300, 120));
	g.addNode(vec2(120, 200));
	g.addNode(vec2(200, 120));
	g.addNode(vec2(100, 100));

	g.setEdge(0, 2);
	g.setEdge(4, 3);
	g.setEdge(2, 1);

	while (updateContext(w))
	{
		for (int i = 0; i < g.size(); ++i)
		{
			draw_point(m, point(g.getPostitions()[i]));
			for (int j = 0; j < g.size(); ++j)
			{
				if (g.getAdjacencyMatrix()[i][j] > 0)
					draw_line(m, line(g.getPostitions()[i], g.getPostitions()[j]));
			}
		}
		
		//draw_aabb(m, a);
		//draw_aabb(m, b);
		//draw_circle(m, c);
	}
	
	closeContext(w);
	
}