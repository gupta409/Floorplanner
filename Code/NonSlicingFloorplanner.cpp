#include "NonSlicingFloorplanner.hpp"
#include "HorizontalGraph.hpp"
#include "VerticalGraph.hpp"
#include "RandomizeUtilites.hpp"
NonSlicingFloorplanner::NonSlicingFloorplanner()
{
	
}

NonSlicingFloorplanner::NonSlicingFloorplanner(list<Node>& nodes)
{
	HorizontalGraph horizontalConstGraph = *new HorizontalGraph();
	VerticalGraph verticalConstGraph = *new VerticalGraph();
	//Add all nodes as vertices in the constraint graphs
	//Add random edges in the graph (left to right or bottom to top connection in this case)
	for (std::list<Node>::iterator it = nodes.begin(); it != nodes.end();++it) {
		this->seq_pair.first.push_back(it->getId());
		this->seq_pair.second.push_back(it->getId());
		it->setOptimumSize(it->getSizeOptions().front());
		Vertex *v1h = new Vertex(*it);
		Vertex *v1v = new Vertex(*it);
		horizontalConstGraph.addVertex(*v1h);
		verticalConstGraph.addVertex(*v1v);
	}
	int i = 0;
	for (std::list<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
		i++;
		std::list<Node>::iterator it1 = nodes.begin();
		std::advance(it1, i);
		for (; it1 != nodes.end(); ++it1) {
			if (it1 != nodes.end()) {
				horizontalConstGraph.addEdge(*horizontalConstGraph.findVertex(it->getId()), *horizontalConstGraph.findVertex(it1->getId()));
			}
		}
	}
	GraphOperations *g1 = new GraphOperations(&horizontalConstGraph);
	GraphOperations *g2 = new GraphOperations(&verticalConstGraph);
	this->horizontalConstGraph = *g1;
	this->verticalConstGraph = *g2;
	printSeqPair();
	for (int i = 0; i < 10; i++) {
		move(i);
	}
	
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
	Edge* hAB = NULL;
	Edge* vAB = NULL;
	Edge* hBA = NULL;
	Edge* vBA = NULL;
	if (hA != NULL && hB != NULL)
		hAB = gh->findEdge(*hA,*hB);
	if (vA != NULL && vB != NULL)
		vAB = gv->findEdge(*vA, *vB);
	if (hA != NULL && hB != NULL)
		hBA = gh->findEdge(*hB, *hA);
	if (vB != NULL && vA != NULL)
		vBA = gv->findEdge(*vB, *vA);
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
			if (hBA != NULL) {
				//Swap edges direction and add to vertical graph
				gh->removeEdge(*hB, *hA);
				gv->addEdge(*vA, *vB);
			}
			else {
				if (vBA != NULL) {
					//Swap edges direction and add to horizontal graph
					gv->removeEdge(*vB, *vA);
					gh->addEdge(*hA, *hB);
				}
				else {
					cout << "invalid state reached";
				}
			}
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
	Edge* hBA = NULL;
	Edge* vBA = NULL;
	Edge* hAB = NULL;
	Edge* vAB = NULL;
	if(hB != NULL && hA != NULL)
		hBA = gh->findEdge(*hB, *hA);
	if (vB != NULL && vA != NULL)
		vBA = gv->findEdge(*vB, *vA);
	if (hA != NULL && hB != NULL)
		hAB = gh->findEdge(*hA, *hB);
	if (vA != NULL && vB != NULL)
		vAB = gv->findEdge(*vA, *vB);
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

void NonSlicingFloorplanner::swapBothSeq(std::string idA, std::string idB) {
	this->swapFirstSeq(idA,idB);
	this->swapSecondSeq(idA,idB);
}

void NonSlicingFloorplanner::move(double temperature)
{
	int moveOption = RandomizeUtilites::getInstance().getRandom(1, 4);
	cout << moveOption << endl;
	//Randomizing Nodes on which move is being performed
	int randomSeq = RandomizeUtilites::getInstance().getRandom(0, 1);
	int randomId1i;
	std::string randomId1,randomId2;
	if (randomSeq == 0) {
		randomId1i = RandomizeUtilites::getInstance().getRandom(0, this->seq_pair.first.size()-2);
		randomId1 = seq_pair.first[randomId1i];
		randomId2 = seq_pair.first[randomId1i+1];
	}
	else {
		randomId1i = RandomizeUtilites::getInstance().getRandom(0, this->seq_pair.second.size()-2);
		randomId1 = seq_pair.second[randomId1i];
		randomId2 = seq_pair.second[randomId1i + 1];
	}
	int option = RandomizeUtilites::getInstance().getRandom(0, horizontalConstGraph.getGraph()->findVertex(randomId1)->getData().getSizeOptions().size()-1);
	std::string temp;
	//Making move
	switch (moveOption)
	{
	case 1:
		//Change Size
		rotateObject(randomId1,option);
		break;
	case 2:
		swapFirstSeq(randomId1, randomId2);
		//Exchange in first seq pair
		temp = seq_pair.first[randomId1i];
		seq_pair.first[randomId1i] = seq_pair.first[randomId1i+1];
		seq_pair.first[randomId1i + 1] = temp;
		break;
	case 3:
		swapSecondSeq(randomId1, randomId2);
		//Exchange in second seq pair
		temp = seq_pair.second[randomId1i];
		seq_pair.second[randomId1i] = seq_pair.second[randomId1i + 1];
		seq_pair.second[randomId1i + 1] = temp;
		break;
	case 4:
		swapBothSeq(randomId1, randomId2);
		//Exchange in both seq pair
		temp = seq_pair.first[randomId1i];
		seq_pair.first[randomId1i] = seq_pair.first[randomId1i + 1];
		seq_pair.first[randomId1i + 1] = temp;
		temp = seq_pair.second[randomId1i];
		seq_pair.second[randomId1i] = seq_pair.second[randomId1i + 1];
		seq_pair.second[randomId1i + 1] = temp;
		break;
	default:
		std::cout << "Invalid Move selected";
		break;
	}
	//Calculating cost
	double length = computeCost(this->horizontalConstGraph);
	double height = computeCost(this->verticalConstGraph);
	double area = length * height;
	cout <<length<<"\t"<<height<<"\t"<< area << endl;
	bool isAccepted = acceptMove(area, temperature);
	//Reverting move if not accepted
	/*if (isAccepted == false) {
		switch (moveOption)
		{
		case 1:
			//Change Size
			rotateObject(randomId1, option);
			break;
		case 2:
			//Exchange in first seq pair
			swapFirstSeq(randomId1, randomId2);
			break;
		case 3:
			swapSecondSeq(randomId1, randomId2);
			//Exchange in second seq pair
			break;
		case 4:
			swapBothSeq(randomId1, randomId2);
			//Exchange in both seq pair
			break;
		default:
			std::cout << "Invalid Move selected";
			break;
		}
	}*/
	printSeqPair();
}

void NonSlicingFloorplanner::printSeqPair()
{
	for (int i = 0; i < seq_pair.first.size(); i++) {
		cout << seq_pair.first[i] << ",";
	}
	cout << endl;
	for (int i = 0; i < seq_pair.second.size(); i++) {
		cout << seq_pair.second[i] << ",";
	}
	cout << endl;
}
