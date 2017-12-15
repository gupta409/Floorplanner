#include "NonSlicingFloorplanner.hpp"
#include "HorizontalGraph.hpp"
#include "VerticalGraph.hpp"
NonSlicingFloorplanner::NonSlicingFloorplanner()
{
	
}

NonSlicingFloorplanner::NonSlicingFloorplanner(list<Node>& nodes)
{
	HorizontalGraph horizontalConstGraph = *new HorizontalGraph();
	VerticalGraph verticalConstGraph = *new VerticalGraph();
	//Add all nodes as vertices in the constraint graphs
	//Add random edges in the graph (left to right or bottom to top connection in this case)
	std::list<Node>::iterator it = nodes.begin();
	it->setOptimumSize(it->getSizeOptions().front());
	Vertex *v1h = new Vertex(*it);
	Vertex *v1v = new Vertex(*it);
	for (; it != nodes.end();++it) {
		horizontalConstGraph.addVertex(*v1h);
		verticalConstGraph.addVertex(*v1v);
		++it;
		if (it!=nodes.end()) {
			it->setOptimumSize(it->getSizeOptions().front());
			Vertex *v2h = new Vertex(*it);
			Vertex *v2v = new Vertex(*it);
			horizontalConstGraph.addVertex(*v2h);
			verticalConstGraph.addVertex(*v2v);
			horizontalConstGraph.addEdge(*v1h, *v2h);
			v1h = v2h;
			v1v = v2v;
		}
		--it;
	}
	GraphOperations *g1 = new GraphOperations(&horizontalConstGraph);
	GraphOperations *g2 = new GraphOperations(&verticalConstGraph);
	this->horizontalConstGraph = *g1;
	this->verticalConstGraph = *g2;
	std::cout<<computeCost(this->horizontalConstGraph)<<endl;
	std::cout << computeCost(this->verticalConstGraph) << endl;
	this->swapSecondSeq("sb1", "sb2");
	std::cout << computeCost(this->horizontalConstGraph) << endl;
	std::cout << computeCost(this->verticalConstGraph) << endl;
}

double NonSlicingFloorplanner::computeCost(GraphOperations & graph)
{
	return graph.getLongestPath();
}

void NonSlicingFloorplanner::rotateObject(std::string id, int option)
{
	Graph* gh = horizontalConstGraph.getGraph();
	Graph* gv = verticalConstGraph.getGraph();
	Node ghNode = gh->findVertex(id)->getData();
	Node gvNode = gv->findVertex(id)->getData();
	if (ghNode.getSizeOptions().size() > option)
	{
		std::list<Size>::iterator it = ghNode.getSizeOptions().begin();
		std::advance(it, option);
		ghNode.setOptimumSize(*it);
		gh->updateWeight(*gh->findVertex(id), ghNode.getOptimumSize().getWidth());
	}
	if (gvNode.getSizeOptions().size() > option)
	{
		std::list<Size>::iterator it = gvNode.getSizeOptions().begin();
		std::advance(it, option);
		gvNode.setOptimumSize(*it);
		gv->updateWeight(*gv->findVertex(id), gvNode.getOptimumSize().getWidth());
	}
}

void NonSlicingFloorplanner::swapFirstSeq(std::string idA, std::string idB)
{
	Graph* gh = horizontalConstGraph.getGraph();
	Graph* gv = verticalConstGraph.getGraph();
	Vertex* hA = gh->findVertex(idA);
	Vertex* hB = gh->findVertex(idB);
	Vertex* vA = gv->findVertex(idA);
	Vertex* vB = gv->findVertex(idB);
	//If edge between A->B in horizontal graph exists
	Edge* hAB = gh->findEdge(*hA,*hB);
	Edge* vAB = gv->findEdge(*vA, *vB);
	if (hAB != NULL) {
		//Swap edges direction and add to vertical graph
		gh->removeEdge(*hA, *hB);
		gv->addEdge(*vB, *vA);
	}
	else {
		if (vAB != NULL) {
			//Swap edges direction and add to horizontal graph
			gv->removeEdge(*vA, *vB);
			gh->addEdge(*hB, *hA);
		}
		else {
			swapFirstSeq(idB, idA);
		}
	}
}

void NonSlicingFloorplanner::swapSecondSeq(std::string idA, std::string idB)
{
	Graph* gh = horizontalConstGraph.getGraph();
	Graph* gv = verticalConstGraph.getGraph();
	Vertex* hA = gh->findVertex(idA);
	Vertex* hB = gh->findVertex(idB);
	Vertex* vA = gv->findVertex(idA);
	Vertex* vB = gv->findVertex(idB);
	Edge* hBA = gh->findEdge(*hB, *hA);
	Edge* vBA = gv->findEdge(*vB, *vA);
	Edge* hAB = gh->findEdge(*hA, *hB);
	Edge* vAB = gv->findEdge(*vA, *vB);
	//If edge between B->A in vertical graph exists
	if (vBA != NULL) {
		//Add to horizontal graph and remove from vertical graph
		gv->removeEdge(*vB, *vA);
		gh->addEdge(*hB, *hA);
	}
	else {
		if (hBA != NULL) {
			//Add to vertical graph and remove from horizontal graph
			gh->removeEdge(*hB, *hA);
			gv->addEdge(*vB, *vA);
		}
		else {
			cout << "Retrying";
			//Try swapping from A->B
			//If edge between A->B in vertical graph exists
			if (vAB != NULL) {
				//Add to horizontal graph and remove from vertical graph
				gv->removeEdge(*vA, *vB);
				gh->addEdge(*hA, *hB);
			}
			else {
				if (hAB != NULL) {
					//Add to vertical graph and remove from horizontal graph
					gh->removeEdge(*hA, *hB);
					gv->addEdge(*vA, *vB);
				}
				else {
					cout << "No connection state";
				}
			}
		}
	}
}