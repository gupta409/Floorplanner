#include "GraphOperations.hpp"

void GraphOperations::performDFS()
{
	int time = 0;
	std::unordered_map<std::string, Vertex*> data = g.getVertices();
	if (data.empty()) {
		std::cout << "Empty Graph Found";
		return;
	}
	else {
		//INIT Vertices
		for (auto it : data) {
			it.second->init();
		}
		//Start DFS
		for (auto it : data) {
			if (!it.second->getIsVisited()) {
				time = DFSVisit(*it.second, time);
			}
		}
	}
}

int GraphOperations::DFSVisit(Vertex &u, int time)
{
	time = time + 1;
	u.setVisitTime(time);
	u.setIsVisited(true);
	unordered_map<std::string, Edge*> edgeList = u.getEdgeList();
	if (!edgeList.empty()) {
		for (auto e : edgeList) {
			if (e.second->getDestination()->getIsVisited() == false) {
				e.second->getDestination()->setPrevious(&u);
				DFSVisit(*e.second->getDestination(), time);
			}
		}
	}
	time = time + 1;
	u.setFinishTime(time);
	topologicalSort.push_back(&u);
	return time;
}

GraphOperations::GraphOperations(Graph g)
{
	this->g = g;
}

Vertex& GraphOperations::addSource()
{
	Vertex source(Node("super_source"));
	std::unordered_map<std::string, Vertex*> data = g.getVertices();
	if (data.empty()) {
		std::cout << "Empty Graph Found";
	}
	else {
		g.addVertex(source);
		for (auto it : data) {
			g.addEdge(source, *it.second, 0);
		}
	}
	return source;
}
Vertex& GraphOperations::addSink()
{
	Vertex sink(Node("super_sink"));
	std::unordered_map<std::string, Vertex*> data = g.getVertices();
	if (data.empty()) {
		std::cout << "Empty Graph Found";
	}
	else {
		g.addVertex(sink);
		for (auto it : data) {
			g.addEdge(*it.second,sink , 0);
		}
	}
	return sink;
}


