#include "Vertex.hpp"
#include "Graph.hpp"
#include "HorizontalGraph.hpp"
#include "VerticalGraph.hpp"
#include "GraphOperations.hpp"
void vertexUnitTest1();
void vertexUnitTest() {
	vertexUnitTest1();
}

void vertexUnitTest1()
{
	Node n1("1");
	Node n2("2");
	Node n3("3");
	Node n4("4");
	Vertex v1(n1);
	Vertex v2(n2);
	Vertex v3(n3);
	Vertex v4(n4);
	Graph g;
	g.addVertex(v1);
	g.addVertex(v2);
	g.addVertex(v3);
	g.addVertex(v4);
	g.addEdge(v1, v2, 1);
	g.addEdge(v2, v3, 2);
	g.addEdge(v3, v4, 3);
	HorizontalGraph hg;
	hg.addVertex(v1);
	hg.addVertex(v2);
	hg.addVertex(v3);
	hg.addVertex(v4);
	hg.addEdge(v1, v2);
	hg.addEdge(v1, v3);
	hg.addEdge(v1, v4);
	hg.addEdge(v2, v1);
	hg.addEdge(v2, v3);
	VerticalGraph vg;
	vg.addVertex(v1);
	vg.addVertex(v2);
	vg.addVertex(v3);
	vg.addVertex(v4);
	vg.addEdge(v1, v2);
	vg.addEdge(v1, v3);
	vg.addEdge(v1, v4);
	vg.addEdge(v2, v1);
	vg.addEdge(v2, v3);
	//Test graph operations
	GraphOperations go1(g);
	GraphOperations goh(hg);
	GraphOperations gov(vg);
	go1.performDFS();
}
