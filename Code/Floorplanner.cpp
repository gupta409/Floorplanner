#include "unordered_map"
#include "Floorplanner.hpp"
#include "PolishUtilities.hpp"
#include "RandomizeUtilites.hpp"
#include "IOUtilites.hpp"
#include "FloorplannerConstants.hpp"
#include "Node.hpp"
#include "algorithm"
#include "stack"
#include "string"
#include <math.h>

//Constructor
Floorplanner::Floorplanner(list<Node>& nodes) {
	for (auto it = nodes.begin(); it != nodes.end(); ++it) {
		std::pair<string, Node*> new_node(it->getId(), &*it);
		this->nodes.insert(new_node);
	}
}
//Finds the optimum size of the Nodes with the specified cut
Node* Floorplanner::sizeNodes(Node& nodeA, Node& nodeB, int cutType) {
	//TODO: Set optimum size based on cut; currently directly using first element of the options: considering only one option for each hard block
	Node* parent;
	list<Size> temp;
	vector<Size> optionsA, optionsB;
	//Extract options from children
	for (auto it : nodeA.getSizeOptions()) {
		optionsA.push_back(Size(it.getLength(), it.getWidth()));
	}
	for (auto it : nodeB.getSizeOptions()) {
		optionsB.push_back(Size(it.getLength(), it.getWidth()));
	}
	if(cutType == Node::HORIZONTAL_CUT){
		//Sort sizeOptions based on: Increasing Width(Height), Decreasing Length(Width)
		//Sort options based on width
		sort(optionsA.begin(),optionsA.end(),Size::compareLengths);
		sort(optionsB.begin(), optionsB.end(), Size::compareLengths);
		//Make new set of options
		list<Size> options;
		for (int i = 0, j = 0; i < optionsA.size() && j < optionsB.size();) {
			double length = max(optionsA[i].getLength(), optionsB[j].getLength());
			double width = optionsA[i].getWidth() + optionsB[j].getWidth();
			options.push_back(Size(length,width));
			if (optionsA[i].getLength() > optionsB[j].getLength()) {
				i++;
			}else
			if (optionsB[j].getLength() >= optionsA[i].getLength()) {
				j++;
			}
		}
		parent = new Node(Node::HORIZONTAL_CUT, &nodeA, &nodeB, options);
		string id = parent->getId();
		pair<string, Node*> new_node(id, parent);
		this->nodes.insert(new_node);
	}else
	if(cutType == Node::VERTICAL_CUT){
		//Sort sizeOptions based on: Increasing Length(Width), Decreasing Width(Heigth)
		//Sort options based on lengths
		sort(optionsA.begin(), optionsA.end(), Size::compareWidths);
		sort(optionsB.begin(), optionsB.end(), Size::compareWidths);
		//Make new set of options
		list<Size> options;
		for (int i = 0, j = 0; i < optionsA.size() && j < optionsB.size();) {
			double length = optionsA[i].getLength() + optionsB[j].getLength();
			double width = max(optionsA[i].getWidth(), optionsB[j].getWidth());
			options.push_back(Size(length, width));
			if (optionsA[i].getWidth() > optionsB[j].getWidth()) {
				i++;
			}else
			{
				j++;
			}
		}
		parent = new Node(Node::VERTICAL_CUT, &nodeA, &nodeB, options);
		string id = parent->getId();
		pair<string, Node*> new_node(id, parent);
		this->nodes.insert(new_node);
	}else{
		//TODO: Throw exception
		cout<<"Invalid Cut";
		parent = NULL;
	}
	return parent;
}
//Converts polish expression to tree and computes sizing and area while converting. Returns: root node of the tree
Node* Floorplanner::polishToTree(const vector<string>& experssion) {
	Node* top;
	Node* n1;
	Node* n2;
	bool isValid = true;
	stack<string> polishStack;
	string temp;
	for(unsigned int i=0;i<experssion.size();i++){
		temp = experssion[i];
		//When cut found the next two in stack should be operands
		if(PolishUtilities::isValidCut(temp)){
			if(!polishStack.empty()){
				if(!PolishUtilities::isValidCut(polishStack.top())){
					n1 = nodes.find(polishStack.top())->second;
					polishStack.pop();
					if(!polishStack.empty()){
						if(!PolishUtilities::isValidCut(polishStack.top())){
							n2 = nodes.find(polishStack.top())->second;
							polishStack.pop();
							top = sizeNodes(*n1,*n2,PolishUtilities::getCutType(temp));
							polishStack.push(top->getId());
						}else{
							//Operator after operand, eg: "|A|"
							isValid = false;
							break;
						}
					}else{
						//One missing operand, eg: "A|"
						isValid = false;
						break;
					}
				}else{
					//Operator after operator, eg: "||"
					isValid = false;
					break;
				}
			}else{
				//No operand or operator after operator,ie Stack is empty eg: "|"
				isValid = false;
				break;
			}
		}
		else{
			//Name block found; add to the stack
			polishStack.push(temp);
		}
	}
	if(polishStack.size()!=1){
		//TODO: Invalid expression found: thorw error
		cout<<"Invalid Expression";
		top = NULL;
	}else{
		if(isValid){
			top = nodes.find(polishStack.top())->second;
			polishStack.pop();
		}else{
			//TODO: Throw exception
			cout<<"Invalid Expression";
			top = NULL;
		}
	}
	return top;
}
//Traverses the tree and gives total area of the floorplan. Returns: Total Area
double Floorplanner::computeCost(Node* root) {
	double cost = 0;
	if (root != NULL) {
		Size optimumSize = root->getOptimumSize();
		cost = optimumSize.getLength()*optimumSize.getWidth();
	}
	else {
		cout << "Null Root found"<<endl;
	}
	return cost;
}
//Returns: True/False based on temperature and deltacost
bool Floorplanner::acceptMove(double deltaCost, double temperature) {
	bool isAccepted = false;
	double boltz;
	double r;
	if (deltaCost < 0) {
		isAccepted = true;
	}
	else {
		boltz = exp(-1*(deltaCost/(FloorplannerConstants::getInstance().getBoltzmanConstant()*temperature)));
		r = RandomizeUtilites::getInstance().getRandomReal(0,1);
		if (r < boltz) {
			isAccepted = true;
		}
	}
	return isAccepted;
}
//Makes changes in the polish expression based on the Wong-Liu Moves model
vector<string> Floorplanner::move(vector<string> currentPolish) {
	int moveOption = RandomizeUtilites::getInstance().getRandom(1, 3);
	//cout << moveOption << endl;
	//Move1: Exchange 2 operands with no other operand in between
	if (moveOption == 1) {
		//Pair of operators,operands index
		pair<vector<int>, vector<int>> indexes = PolishUtilities::getLocations(currentPolish);
		int randomPoint = RandomizeUtilites::getInstance().getRandom(0, indexes.second.size() - 1);
		int randomOperandIndex1 = indexes.second[randomPoint];
		int randomOperandIndex2;
		if (randomPoint < indexes.second.size() - 1) {
			randomOperandIndex2 = indexes.second[randomPoint + 1];
		}
		else {
			randomOperandIndex2 = indexes.second[randomPoint - 1];
		}
		string temp = currentPolish.at(randomOperandIndex1);
		currentPolish[randomOperandIndex1] = currentPolish.at(randomOperandIndex2);
		currentPolish[randomOperandIndex2] = temp;
	}
	//Move2: Complement a series of operators between two operands
	if (moveOption == 2) {
		vector<pair<int, int>> validOperatorSeries = PolishUtilities::getRepOperators(currentPolish);
		//Checks if such operator/operands are present
		if (validOperatorSeries.size() > 0) {
			int randomPoint = RandomizeUtilites::getInstance().getRandom(0, validOperatorSeries.size() - 1);
			for (int i = validOperatorSeries[randomPoint].first; i <= validOperatorSeries[randomPoint].second; i++) {
				currentPolish[i] = PolishUtilities::getCompliment(currentPolish[i]);
			}
		}
	}
	//Move3: Exchange adjecnt operator and operand if resultant is still normalized polish expression
	if (moveOption == 3) {
		vector<int> validIndices = PolishUtilities::getSurroundedOperands(currentPolish);
		//Checks if such operator/operands are present
		if (validIndices.size() > 0) {
			int randomPoint = RandomizeUtilites::getInstance().getRandom(0, validIndices.size() - 1);
			string temp = currentPolish.at(validIndices[randomPoint]);
			currentPolish[validIndices[randomPoint]] = currentPolish.at(validIndices[randomPoint] + 1);
			currentPolish[validIndices[randomPoint] + 1] = temp;
		}
	}
	return currentPolish;
}
//Returns new temperature
double Floorplanner::coolDown(double temperature) {
	return temperature*FloorplannerConstants::getInstance().getCoolDownRate();
	//return exp(-1*FloorplannerConstants::getInstance().getCoolDownRate())*temperature;
}
double Floorplanner::coolDownMoves(double movesPerStep) {
	//return exp(-1 * FloorplannerConstants::getInstance().getCoolDownRate())*movesPerStep;
	return FloorplannerConstants::getInstance().getMovesCoolDown()*movesPerStep;
}
//Simulated Annealing performed here
Node* Floorplanner::floorplan() {
	//string dumpData = "IterationNo,Temperature, Moves, CurrentCost, DeltaCost\n";
	string dumpData = "Temperature,%AcceptedMove\n";
	int moveCounter = 0, acceptedMoveCounter = 0;
	vector<string> currentExpression = generateInitialExpression();
	double temperature = FloorplannerConstants::getInstance().getStartTemp();
	double movesPerStep = FloorplannerConstants::getInstance().getMovesPerStep();
	Node* root = NULL;
	double delCost, newCost, currentCost;
	currentCost = computeCost(polishToTree(currentExpression));
	vector<string> newExpression;
	int temp = movesPerStep;
	int MAX_MOVES = 1000;
	int MIN_MOVES = 50;
	std::cout << "Calculating -" << std::flush;
	while(temperature > FloorplannerConstants::getInstance().getFreezingTemperature()){
		temp = movesPerStep;
		for (int i = 1; i <= movesPerStep; i++) {
			newExpression = move(currentExpression);
			newCost = computeCost(polishToTree(newExpression));
			delCost = newCost - currentCost;
			moveCounter++;
			//Animation for console display
			if(moveCounter%5 == 0){
				std::cout << "\b\\" << std::flush;
			}
			if(moveCounter%5 == 1){
				std::cout << "\b|" << std::flush;
			}
			if(moveCounter%5 == 2){
				std::cout << "\b/" << std::flush;
			}
			if(moveCounter%5 == 3){
				std::cout << "\b-" << std::flush;
			}
			//If move accepted
			if (acceptMove(delCost, temperature)) {
				//Log results
				acceptedMoveCounter++;
				dumpData = dumpData+ std::to_string(moveCounter) +","+ std::to_string(temperature)+"," + std::to_string(movesPerStep) +"," + std::to_string(currentCost)+"," + std::to_string(delCost)+"\n";
				//Lock changes
				currentExpression = newExpression;
				currentCost = newCost;
				//Dynamic change in MovesPerStep
				if (delCost<0) {
					if(movesPerStep < MAX_MOVES){
						movesPerStep = movesPerStep+ 10;
					}
				}
				if (delCost == 0) {
					if(movesPerStep > MIN_MOVES){
						movesPerStep = movesPerStep - 10;
					}
				}
			}
		}
		movesPerStep = temp;
		temperature = coolDown(temperature);
		movesPerStep = coolDownMoves(movesPerStep);
	}
	root = polishToTree(currentExpression);
	//Compute co-ordinates
	if (root != NULL) {
		assignOptimum(root);
		cout << computeCost(root) << endl;
		root->setLLCord(pair<double, double>(0, 0));
		root->setURCord(pair<double, double>(root->getOptimumSize().getLength(), root->getOptimumSize().getWidth()));
		processCords(root);
		cleanupNodes();
	}
	else {
		//TODO: Throw exception
		cout << "ERROR: Null root found.";
	}
	dumpData = dumpData + "\n Attempted Moves: " + std::to_string(moveCounter) + "\n Accepted Moves: " + std::to_string(acceptedMoveCounter);
	IOUtilites::getInstance().dumpData(dumpData);
	return root;
}

//Prints sizing of all the nodes in the tree
void Floorplanner::printNodes(){
	for(auto it = this->nodes.begin(); it != this->nodes.end(); ++it){
		cout<<"ID:\t"<<it->first<<" Length:\t"<<it->second->getOptimumSize().getLength()<<" Width:\t"<<it->second->getOptimumSize().getWidth()<<endl;
	}
}

unordered_map<string, Node*> Floorplanner::getNodes()
{
	return nodes;
}

//Function currently generates initial expression of the form AB|C-D|E-F|G|
vector<string> Floorplanner::generateInitialExpression(){
	vector<string> expression;
	auto it = nodes.begin();
	if(nodes.size()>=2){
		expression.push_back(it->second->getId());
		++it;
		expression.push_back(it->second->getId());
		expression.push_back(PolishUtilities::VERTICAL_CUT);
	}else{
		//TODO: Throw error
		cout<<"Too few nodes in floorplan";
		//FIXME: Handle error and give output as same node itself
	}
	int i = 1;
	if(nodes.size()>2){
		++it;
		for(; it!=nodes.end();++it, i++){
			expression.push_back(it->second->getId());
			if(i%2==0){
				expression.push_back(PolishUtilities::VERTICAL_CUT);
			}else{
				expression.push_back(PolishUtilities::HORIZONTAL_CUT);
			}
		}
	}
	return expression;
}

//Function to find and set co-ordinates
void Floorplanner::processCords(Node* root) {
	if (root->isEndNode()) {
		return;
	}
	else {
		Node* left = root->getLeft();
		Node* right = root->getRight();
		left->setLLCord(root->getLLCord());
		right->setURCord(root->getURCord());
		if (root->getCutType() == Node::HORIZONTAL_CUT) {
			left->setURCord(pair<double,double>(root->getLLCord().first + left->getOptimumSize().getLength(), root->getLLCord().second+left->getOptimumSize().getWidth()));
			right->setLLCord(pair<double, double>(root->getURCord().first - right->getOptimumSize().getLength(),root->getURCord().second - right->getOptimumSize().getWidth()));
		}
		if (root->getCutType() == Node::VERTICAL_CUT) {
			left->setURCord(pair<double,double>(root->getLLCord().first + left->getOptimumSize().getLength(),root->getLLCord().second+left->getOptimumSize().getWidth()));
			right->setLLCord(pair<double, double>(root->getURCord().first - right->getOptimumSize().getLength(), root->getURCord().second - right->getOptimumSize().getWidth()));
		}
	}
	processCords(root->getLeft());
	processCords(root->getRight());
}
void Floorplanner::cleanupNodes() {
	//Clean data in container
	int size = nodes.size();
	int k = 0;
	auto it = nodes.begin();
	int j = 0;
	// erase all odd numbers from c
	for (int i=size; i>0; i--) {
		if (!it->second->isEndNode()) {
			k++;
			//cout << it->second->getId() << endl;
			it = this->nodes.erase(it);
		}
		else {
			j++;
			++it;
		}
	}
}
double Floorplanner::computeNetArea() {
	double area = 0;
	for (auto it:nodes) {
		area = area + it.second->getOptimumSize().getLength() * it.second->getOptimumSize().getWidth();
	}
	return area;
}
double Floorplanner::computeBlackArea(Node * root) {
	double blackArea = computeCost(root)- computeNetArea();
	return blackArea;
}

void Floorplanner::assignOptimum(Node* root) {
	if (root->getParent()==NULL) {
		//FIXME: Poor complexity here
		vector<Size> options;
		for (auto it : root->getSizeOptions()) {
			options.push_back(it);
		}
		//Root node found pick size directly by sorting
		sort(options.begin(), options.end(), Size::compareArea);
		Size s = options.front();
		root->setOptimumSize(s);
	}
	if(!root->isEndNode()) {
		//Find optimum of both children nodes
		Node* left = root->getLeft();
		Node* right = root->getRight();
		vector<Size> leftOptions, rightOptions;
		if (root->getCutType() == Node::HORIZONTAL_CUT) {
			//Create set of options with child.length <= root.length
			for (auto it : left->getSizeOptions()) {
				if (it.getLength() <= root->getOptimumSize().getLength()) {
					leftOptions.push_back(it);
				}
			}
			for (auto it : right->getSizeOptions()) {
				if (it.getLength() <= root->getOptimumSize().getLength()) {
					rightOptions.push_back(it);
				}
			}
			//Traverse through all optons to find the combination which create the same width
			for (auto lit : leftOptions) {
				for (auto rit : rightOptions) {
					if (lit.getWidth() + rit.getWidth() == root->getOptimumSize().getWidth()) {
						left->setOptimumSize(lit);
						right->setOptimumSize(rit);
						break;
					}
				}
			}
		}
		else {
			//Create set of options with child.width <= root.width
			for (auto it : left->getSizeOptions()) {
				if (it.getWidth() <= root->getOptimumSize().getWidth()) {
					leftOptions.push_back(it);
				}
			}
			for (auto it : right->getSizeOptions()) {
				if (it.getWidth() <= root->getOptimumSize().getWidth()) {
					rightOptions.push_back(it);
				}
			}
			//Traverse through all optons to find the combination which create the same length as root
			for (auto lit : leftOptions) {
				for (auto rit : rightOptions) {
					if (lit.getLength() + rit.getLength() == root->getOptimumSize().getLength()) {
						left->setOptimumSize(lit);
						right->setOptimumSize(rit);
						break;
					}
				}
			}
		}
		//Call assignOptimum() for all daughter nodes
		assignOptimum(root->getLeft());
		assignOptimum(root->getRight());
	}
	else {
		//End node found
		return;
	}
}
