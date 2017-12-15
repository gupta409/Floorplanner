#pragma once
#include"Graph.hpp"
class HorizontalGraph : public Graph
{
public:
	bool addEdge(Vertex &source, Vertex &destination);
};