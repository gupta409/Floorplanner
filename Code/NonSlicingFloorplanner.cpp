#include "NonSlicingFloorplanner.hpp"
#include "HorizontalGraph.hpp"
#include "VerticalGraph.hpp"
#include "RandomizeUtilites.hpp"
#include "FloorplannerConstants.hpp"
#include "IOUtilites.hpp"
NonSlicingFloorplanner::NonSlicingFloorplanner()
{

}

NonSlicingFloorplanner::NonSlicingFloorplanner(list<Node>& nodes)
{
	this->horizontalConstGraph = new GraphOperations(new HorizontalGraph());
	this->verticalConstGraph = new GraphOperations(new VerticalGraph());
	//Add all nodes as vertices in the constraint graphs
	//Add random edges in the graph (left to right or bottom to top connection in this case)
	for (std::list<Node>::iterator it = nodes.begin(); it != nodes.end();++it) {
		this->seq_pair.first.push_back(it->getId());
		this->seq_pair.second.push_back(it->getId());
		it->setOptimumSize(it->getSizeOptions().front());
		Vertex *v1h = new Vertex(*it);
		Vertex *v1v = new Vertex(*it);
		this->horizontalConstGraph->getGraph()->addVertex(*v1h);
		this->verticalConstGraph->getGraph()->addVertex(*v1v);
	}
	int i = 0;
	for (std::list<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
		i++;
		std::list<Node>::iterator it1 = nodes.begin();
		std::advance(it1, i);
		for (; it1 != nodes.end(); ++it1) {
			if (it1 != nodes.end()) {
				this->horizontalConstGraph->getGraph()->addEdge(*this->horizontalConstGraph->getGraph()->findVertex(it->getId()), *this->horizontalConstGraph->getGraph()->findVertex(it1->getId()));
			}
		}
	}
}

double NonSlicingFloorplanner::computeCost(GraphOperations & graph)
{
	return graph.getLongestPath();
}

void NonSlicingFloorplanner::rotateObject(std::string id, int option)
{
	Graph* gh = horizontalConstGraph->getGraph();
	Graph* gv = verticalConstGraph->getGraph();
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
	Graph* gh = horizontalConstGraph->getGraph();
	Graph* gv = verticalConstGraph->getGraph();
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
		//cout << "Zero" << endl;
		gh->removeEdge(*hA, *hB);
		gv->addEdge(*vB, *vA);
	}
	else {
		if (vAB != NULL) {
			//Swap edges direction and add to horizontal graph
			//cout << "One" << endl;
			gv->removeEdge(*vA, *vB);
			gh->addEdge(*hB, *hA);
		}
		else {
			if (hBA != NULL) {
				//Swap edges direction and add to vertical graph
				//cout << "Two" << endl;
				gh->removeEdge(*hB, *hA);
				gv->addEdge(*vA, *vB);
			}
			else {
				if (vBA != NULL) {
					//Swap edges direction and add to horizontal graph
					//cout << "Three" << endl;
					gv->removeEdge(*vB, *vA);
					gh->addEdge(*hA, *hB);
				}
				else {
					cout << "invalid state reached"<<endl;
				}
			}
		}
	}
}

void NonSlicingFloorplanner::swapSecondSeq(std::string idA, std::string idB)
{
	Graph* gh = horizontalConstGraph->getGraph();
	Graph* gv = verticalConstGraph->getGraph();
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
			//cout << "Retrying";
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
					//cout << "No connection state";
				}
			}
		}
	}
}

void NonSlicingFloorplanner::swapBothSeq(std::string idA, std::string idB) {
	this->swapFirstSeq(idA,idB);
	this->swapSecondSeq(idA,idB);
}

pair<double,bool>* NonSlicingFloorplanner::move(double previousCost, double temperature)
{
	int moveOption = 4;//RandomizeUtilites::getInstance().getRandom(1, 4);
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
	int option = RandomizeUtilites::getInstance().getRandom(0, horizontalConstGraph->getGraph()->findVertex(randomId1)->getData().getSizeOptions().size()-1);
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
	double length = computeCost(*horizontalConstGraph);
	double height = computeCost(*verticalConstGraph);
	double area = length * height;
	if (area <= 221679) {
		cout <<endl << "ALERT" << area<<endl;
	}
	bool isAccepted = acceptMove(area-previousCost, temperature);
	//Reverting move if not accepted
	if (isAccepted == false) {
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
	}
	return new std::pair<double,bool>(area,isAccepted);
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

unordered_map<std::string, Node*> * NonSlicingFloorplanner::processCords() {
	unordered_map<std::string, Node*> *nodes = new unordered_map<std::string, Node*> ;
	horizontalConstGraph->processCordsH();
	for (auto g : horizontalConstGraph->getGraph()->getVertices()) {
		Node* newNode = new Node(g.second->getData().getId());
		newNode->setLLCord(g.second->getData().getLLCord());
		newNode->setURCord(g.second->getData().getURCord());
		if (newNode->getId().compare("super_source") == 0)
			continue;
		if (newNode->getId().compare("super_sink") == 0)
			continue;
		nodes->insert(std::pair<std::string, Node*>(newNode->getId(), newNode));
	}
	verticalConstGraph->processCordsV();
	for (auto g : verticalConstGraph->getGraph()->getVertices()) {
		if (nodes->find(g.second->getData().getId()) != nodes->end()) {
			nodes->find(g.second->getData().getId())->second->setLLCord(std::pair<double, double>(nodes->find(g.second->getData().getId())->second->getLLCord().first, g.second->getData().getLLCord().second));
			nodes->find(g.second->getData().getId())->second->setURCord(std::pair<double, double>(nodes->find(g.second->getData().getId())->second->getURCord().first, g.second->getData().getURCord().second));
		}
	}
	return nodes;
}


//Simulated Annealing performed here
void NonSlicingFloorplanner::floorplan() {
	//string dumpData = "IterationNo,Temperature, Moves, CurrentCost, DeltaCost\n";
	//string dumpData = "Temperature,%AcceptedMove\n";
	int moveCounter = 0, acceptedMoveCounter = 0;
	double temperature = FloorplannerConstants::getInstance().getStartTemp();
	double movesPerStep = FloorplannerConstants::getInstance().getMovesPerStep();
	Node* root = NULL;
	double delCost, newCost, currentCost;
	currentCost = computeCost(*horizontalConstGraph)*computeCost(*verticalConstGraph);
	int temp = movesPerStep;
	int MAX_MOVES = 1000;
	int MIN_MOVES = 50;
	std::cout << "Calculating -" << std::flush;
	while (temperature > FloorplannerConstants::getInstance().getFreezingTemperature()) {
		temp = movesPerStep;
		for (int i = 1; i <= movesPerStep; i++) {
			pair<double,bool> *moveResults = move(currentCost,temperature);
			delCost = moveResults->first - currentCost;

			moveCounter++;
			/*//Animation for console display
			if (moveCounter % 5 == 0) {
				std::cout << "\b\\" << std::flush;
			}
			if (moveCounter % 5 == 1) {
				std::cout << "\b|" << std::flush;
			}
			if (moveCounter % 5 == 2) {
				std::cout << "\b/" << std::flush;
			}
			if (moveCounter % 5 == 3) {
				std::cout << "\b-" << std::flush;
			}*/
			//If move accepted
			if (moveResults->second) {
				//Log results
				cout << moveResults->first << endl;
				acceptedMoveCounter++;
		//		dumpData = dumpData + std::to_string(moveCounter) + "," + std::to_string(temperature) + "," + std::to_string(movesPerStep) + "," + std::to_string(currentCost) + "," + std::to_string(delCost) + "\n";
				//Lock changes
				currentCost = moveResults->first;
				//Dynamic change in MovesPerStep
				if (delCost<0) {
					if (movesPerStep < MAX_MOVES) {
						movesPerStep = movesPerStep + 10;
					}
				}
				if (delCost == 0) {
					if (movesPerStep > MIN_MOVES) {
						movesPerStep = movesPerStep - 10;
					}
				}
			}
			delete moveResults;
		}
		movesPerStep = temp;
		temperature = coolDown(temperature);
		movesPerStep = coolDownMoves(movesPerStep);
	}
	//Compute Final areas
	this->usedArea = currentCost;
	this->netArea = 0;
	for (auto g : horizontalConstGraph->getGraph()->getVertices()) {
		this->netArea = this->netArea + g.second->getData().getOptimumSize().getLength()*g.second->getData().getOptimumSize().getWidth();
	}
	this->blackArea = usedArea - netArea;
	//dumpData = dumpData + "\n Attempted Moves: " + std::to_string(moveCounter) + "\n Accepted Moves: " + std::to_string(acceptedMoveCounter);
	//IOUtilites::getInstance().dumpData(dumpData);
	//Finding the co-ordinates
	unordered_map<std::string, Node*> *nodes = new unordered_map<std::string, Node*> ;
	for(auto v: verticalConstGraph->getTopologicalSort()){
		Vertex* g = horizontalConstGraph->getGraph()->findVertex(v->getData().getId());
		double xD = g->getDistance();
		double yD = v->getDistance();
		Node* newNode = new Node(g->getData().getId());
		//Add lower left and upper rigth co-ordinates
		newNode->setLLCord(std::pair<double,double>(xD,yD));
		double width = g->getData().getOptimumSize().getWidth();
		double height = g->getData().getOptimumSize().getLength();
		newNode->setURCord(std::pair<double, double>(xD+width, yD+height));
		if (newNode->getId().compare("super_source") == 0)
			continue;
		if (newNode->getId().compare("super_sink") == 0)
			continue;
		nodes->insert(std::pair<std::string, Node*>(newNode->getId(), newNode));
	}
	finalData = nodes;
	return;
}

double NonSlicingFloorplanner::getBlackArea(){
	return this->blackArea;
}
double NonSlicingFloorplanner::getUsedArea(){
	return this->usedArea;
}
unordered_map<std::string, Node*> * NonSlicingFloorplanner::getFinalData(){
	return finalData;
}
