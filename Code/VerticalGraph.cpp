#include "VerticalGraph.hpp"

bool VerticalGraph::addEdge(Vertex & source, Vertex & destination)
{
	std::unordered_map<std::string, Vertex*>::const_iterator got = vertices.find(source.getData().getId());
	if (got == vertices.end()) {
		std::cout << "Source Vertex not found";
		return false;
	}
	else {
		source.addEdge(destination, source.getData().getOptimumSize().getLength());
		return true;
	}
}


