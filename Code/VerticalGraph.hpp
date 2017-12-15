#pragma once
#include "Graph.hpp"
class VerticalGraph : public Graph
{
public:

	bool addEdge(Vertex &source, Vertex &destination);
};