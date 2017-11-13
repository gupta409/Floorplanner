#include "unordered_map"
#include "Floorplanner.hpp"
#include "PolishUtilities.hpp"
#include "RandomizeUtilites.hpp"
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
	Size defaultSize(0,0);
	if (nodeA.isEndNode()) {
		if (!nodeA.getSizeOptions().empty()) {
			nodeA.setOptimumSize(nodeA.getSizeOptions().front());
		}
		else {
			nodeA.setOptimumSize(defaultSize);
		}
	}
	if (nodeB.isEndNode()) {
		if (!nodeB.getSizeOptions().empty()) {
			nodeB.setOptimumSize(nodeB.getSizeOptions().front());
		}
		else {
			nodeB.setOptimumSize(defaultSize);
		}
	}
	if(cutType == Node::HORIZONTAL_CUT){
		parent = new Node(Node::HORIZONTAL_CUT, &nodeA, &nodeB);
		double length = max(nodeA.getOptimumSize().getLength(),nodeB.getOptimumSize().getLength());
		double width = nodeA.getOptimumSize().getWidth()+nodeB.getOptimumSize().getWidth();
		Size s(length,width);
		parent->setOptimumSize(s);
		std::pair<string,Node*> new_node(parent->getId(),parent);
		this->nodes.insert(new_node);
	}else
	if(cutType == Node::VERTICAL_CUT){
		parent = new Node(Node::VERTICAL_CUT, &nodeA, &nodeB);
		double length = nodeA.getOptimumSize().getLength()+nodeB.getOptimumSize().getLength();
		double width = max(nodeA.getOptimumSize().getWidth(),nodeB.getOptimumSize().getWidth());
		Size s(length,width);
		parent->setOptimumSize(s);
		std::pair<string,Node*> new_node(parent->getId(),parent);
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
	cost = root->getOptimumSize().getLength()*root->getOptimumSize().getWidth();
	return cost;
}
//Returns: True/False
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
	//int moveOption = 3;
	//cout << moveOption << endl;
	//Move1: Exchange 2 operands with no other operand in between
	if (moveOption == 1) {
		//Pair of operators,operands index
		pair<vector<int>, vector<int>> indexes = PolishUtilities::getLocations(currentPolish);
		int randomPoint = RandomizeUtilites::getInstance().getRandom(0, indexes.second.size() - 1);
		int randomOperandIndex1 = indexes.second[randomPoint];
		int randomOperandIndex2;
		if (randomPoint <indexes.second.size() - 1) {
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
	vector<string> currentExpression = generateInitialExpression();
	double temperature = FloorplannerConstants::getInstance().getStartTemp();
	double movesPerStep = FloorplannerConstants::getInstance().getMovesPerStep();
	Node* root = NULL;
	double delCost, newCost, currentCost;
	currentCost = computeCost(polishToTree(currentExpression));
	//cout << "Orignal Cost:" << currentCost<<endl;
	vector<string> newExpression;
	while(temperature > FloorplannerConstants::getInstance().getFreezingTemperature()){
		for (int i = 1; i <= movesPerStep; i++) {
			newExpression = move(currentExpression);
			newCost = computeCost(polishToTree(newExpression));
			delCost = newCost - currentCost;
			if (acceptMove(delCost, temperature)) {
				cout <<"Temperature:\t"<<temperature<<"\t"<< "DelCost\t" << delCost << endl;
				//Lock changes
				currentExpression = newExpression;
				currentCost = newCost;
			}
		}
		temperature = coolDown(temperature);
		movesPerStep = coolDownMoves(movesPerStep);
	}
	root = polishToTree(currentExpression);
	cout << computeCost(root)<<endl;
	//Compute co-ordinates
	if (root != NULL) {
		root->setLLCord(pair<double, double>(0, 0));
		root->setURCord(pair<double, double>(root->getOptimumSize().getLength(), root->getOptimumSize().getWidth()));
		processCords(root);
		cleanupNodes();
	}
	else {
		//TODO: Throw exception
		cout << "ERROR: Null root found.";
	}
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
	if (root == NULL) {
		cout << "processCords(): NULL input given"<<endl;
		return;
	}
	if (root->isEndNode()) {
		return;
	}
	else {
		Node* left = root->getLeft();
		Node* right = root->getRight();
		left->setLLCord(root->getLLCord());
		right->setURCord(root->getURCord());
		if (root->getCutType() == Node::HORIZONTAL_CUT) {
			left->setURCord(pair<double,double>(root->getURCord().first, root->getLLCord().second+left->getOptimumSize().getWidth()));
			right->setLLCord(pair<double, double>(root->getLLCord().first,root->getLLCord().second+left->getOptimumSize().getWidth()));
		}
		if (root->getCutType() == Node::VERTICAL_CUT) {
			left->setURCord(pair<double,double>(root->getLLCord().first,root->getLLCord().second+left->getOptimumSize().getLength()));
			right->setLLCord(pair<double, double>(root->getURCord().first - right->getOptimumSize().getLength(), root->getLLCord().second));
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
	
//Makes changes in the polish expression based on the Wong-Liu Moves model
vector<string> Floorplanner::fastMove(vector<string> currentPolish) {
	Node* sizingNode = NULL;
	int moveOption = RandomizeUtilites::getInstance().getRandom(1, 3);
	//int moveOption = 1;
	cout << moveOption << endl;
	//Move1: Exchange 2 operands with no other operand in between
	if (moveOption == 1) {
		//Pair of operators,operands index
		pair<vector<int>, vector<int>> indexes = PolishUtilities::getLocations(currentPolish);
		int randomPoint = RandomizeUtilites::getInstance().getRandom(0, indexes.second.size() - 1);
		int randomOperandIndex1 = indexes.second[randomPoint];
		int randomOperandIndex2;
		if (randomPoint <indexes.second.size() - 1) {
			randomOperandIndex2 = indexes.second[randomPoint + 1];
		}
		else {
			randomOperandIndex2 = indexes.second[randomPoint - 1];
		}
		//Making changes in tree
		Node* operand1 = nodes.find(currentPolish.at(randomOperandIndex1))->second;
		Node* operand2 = nodes.find(currentPolish.at(randomOperandIndex2))->second;
		//Swap nodes
		swapNodes(operand1,operand2);
		//Size parent1 and parent2
		sizeNode(operand1->getParent());
		sizeNode(operand2->getParent());
		//FIXME: Not needed
		//Making changes in polish
		string temp = currentPolish.at(randomOperandIndex1);
		currentPolish[randomOperandIndex1] = currentPolish.at(randomOperandIndex2);
		currentPolish[randomOperandIndex2] = temp;
	}
	//Move2: Complement a series of operators between two operands
	/*if (moveOption == 2) {
		vector<pair<int, int>> validOperatorSeries = PolishUtilities::getRepOperators(currentPolish);
		//Checks if such operator are present
		if (validOperatorSeries.size() > 0) {
			int randomPoint = RandomizeUtilites::getInstance().getRandom(0, validOperatorSeries.size() - 1);
			for (int i = validOperatorSeries[randomPoint].first; i <= validOperatorSeries[randomPoint].second; i++) {
				currentPolish[i] = PolishUtilities::getCompliment(currentPolish[i]);
			}
		}
	}*/
	//Move3: Exchange adjecnt operator and operand if resultant is still normalized polish expression
	if (moveOption == 3) {
		vector<int> validIndices = PolishUtilities::getSurroundedOperands(currentPolish);
		//Checks if such operator/operands are present
		if (validIndices.size() > 0) {
			int randomPoint = RandomizeUtilites::getInstance().getRandom(0, validIndices.size() - 1);
			//int randomPoint = 3;
			//Make changes in tree
			Node* operand1;
			//Check if node is an operand only
			if (!PolishUtilities::isValidCut(currentPolish[validIndices[randomPoint] + 1]))
				operand1 = nodes.find(currentPolish[validIndices[randomPoint] + 1])->second;
			else {
				//If operator found
				if (!PolishUtilities::isValidCut(currentPolish[validIndices[randomPoint]])) 
					operand1 = nodes.find(currentPolish[validIndices[randomPoint]])->second;
				else {
					cout << "fastMove(): MOVE 3: Invalid exchange asked"<<endl;
					return currentPolish;
				}
			}
			Node* operand2 = NULL;
			//Find second operand
			if (operand1->isLeftChild()) {
				//operand 1 is left node
				if (!operand1->getParent()->getRight()->isEndNode()) {
					//AB|C- like case1: Currently pointing to C
					operand2 = operand1->getParent()->getRight()->getRight();
					swapNodes(operand1, operand2);
					Node* operand3 = operand1->getParent()->getLeft();
					swapNodes(operand1, operand3);
					//Resize parents
					sizeNode(operand1->getParent());
					sizeNode(operand2->getParent());
				}
				else {
					//FIXME: Surely some issue here
					//AB|CD-| like case exchange D
					Node* op1Parent = operand1->getParent();
					Node* operand3;
					if (op1Parent->isLeftChild()) {
							//Get AB|
							operand2 = op1Parent->getParent()->getRight();
							//Get C
							operand3 = op1Parent->getRight();
							//swap(AB|, C)
							swapNodes(operand2, operand3);
							//swap(D,C)
							swapNodes(operand1, operand3);
							//swap(parent of C, D)
							swapNodes(operand3->getParent(), operand1);
							//Resize parents of D
							sizeNode(operand1->getParent());
							//Resize parent of C
							sizeNode(operand3->getParent());
					}
					else if (op1Parent->isRightChild()) {
							//Get AB|
							operand2 = op1Parent->getParent()->getLeft();
							//Get C
							operand3 = op1Parent->getRight();
							//swap(AB|, C)
							swapNodes(operand2, operand3);
							//swap(D,C)
							swapNodes(operand1, operand3);
							//swap(parent of C, D)
							swapNodes(operand3->getParent(), operand1);
							//Resize parents of D
							sizeNode(operand1->getParent());
							//Resize parent of C
							sizeNode(operand3->getParent());
					}
					else {
						cout << "fastMove(): Invalid node";
						return currentPolish;
					}
				}
			}else if (operand1->isRightChild()) {
				//operand 1 is right node
				if (!operand1->getParent()->getLeft()->isEndNode()) {
					//AB|C- like case
					operand2 = operand1->getParent()->getLeft()->getLeft();
					swapNodes(operand1, operand2);
					Node* operand3 = operand1->getParent()->getRight();
					swapNodes(operand1, operand2);
					//Resize parents
					sizeNode(operand1->getParent());
					sizeNode(operand2->getParent());
				}
				else {
					//FIXME: Surely some issue here
					//AB|CD-| like case exchange D
					Node* op1Parent = operand1->getParent();
					Node* operand3;
					if (op1Parent->isLeftChild()) {
						//Get AB|
						operand2 = op1Parent->getParent()->getRight();
						//Get C
						operand3 = op1Parent->getLeft();
						//swap(AB|, C)
						swapNodes(operand2, operand3);
						//swap(D,C)
						swapNodes(operand1, operand3);
						//swap(parent of C, D)
						swapNodes(operand3->getParent(), operand1);
						//Resize parents of D
						sizeNode(operand1->getParent());
						//Resize parent of C
						sizeNode(operand3->getParent());
					}
					else if (op1Parent->isRightChild()) {
						//Get AB|
						operand2 = op1Parent->getParent()->getLeft();
						//Get C
						operand3 = op1Parent->getLeft();
						//swap(AB|, C)
						swapNodes(operand2, operand3);
						//swap(D,C)
						swapNodes(operand1, operand3);
						//swap(parent of C, D)
						swapNodes(operand3->getParent(), operand1);
						//Resize parents of D
						sizeNode(operand1->getParent());
						//Resize parent of C
						sizeNode(operand3->getParent());
					}
					else {
						cout << "fastMove(): Invalid node";
						return currentPolish;
					}
				}
			}
			else {
				cout << "Invalid Move 3 asked for";
				return currentPolish;
			}
			
			//Change polish
			string temp = currentPolish.at(validIndices[randomPoint]);
			currentPolish[validIndices[randomPoint]] = currentPolish.at(validIndices[randomPoint] + 1);
			currentPolish[validIndices[randomPoint] + 1] = temp;
		}
	}
	return currentPolish;
}
//Swaps any two nodes of the tree
void Floorplanner::swapNodes(Node* a, Node* b) {
	if (a != NULL && b != NULL) {
		Node* parentA = a->getParent();
		Node* parentB = b->getParent();
		if (parentA !=NULL && parentB != NULL) {
			if (parentA == parentB) {
				if (a->isLeftChild() && b->isRightChild()) {
					parentA->setLeft(b);
					parentA->setRight(a);
				}
				else {
					parentA->setLeft(a);
					parentA->setRight(b);
				}
			}
			else {
				//Change left node of parent of a
				if (a->isLeftChild()) {
					parentA->setLeft(b);
				}
				else {
					//Change right node of parent of a
					if (a->isRightChild()) {
						parentA->setRight(b);
					}
					else {
						cout << endl << "swapNodes(): Invalid child input" << endl;
					}
				}
				//Change left node of parent of b
				if (b->isLeftChild()) {
					parentB->setLeft(a);
				}
				else {
					//Change right node of parent of b
					if (b->isRightChild()) {
						parentB->setRight(a);
					}
					else {
						cout << endl << "swapNodes(): Invalid child input" << endl;
					}
				}
			}
		
			//Change parent of a
			a->setParent(parentB);
			//Change parent of b
			b->setParent(parentA);
		}
		else {
			cout << "swapNodes(): Parents are null";
		}
	}
	else {
		cout << "swapNodes(): Node A or Node B is NULL";
	}
}
//Re-size nodes
void Floorplanner::sizeNode(Node* root) {
	Node* parent = root->getParent();
	if (parent != NULL) {
		int cutType = parent->getCutType();
		Node* nodeA = parent->getLeft();
		Node* nodeB = parent->getRight();
		Size defaultSize(0, 0);
		if (nodeA->isEndNode()) {
			if (!nodeA->getSizeOptions().empty()) {
				nodeA->setOptimumSize(nodeA->getSizeOptions().front());
			}
			else {
				nodeA->setOptimumSize(defaultSize);
			}
		}
		if (nodeB->isEndNode()) {
			if (!nodeB->getSizeOptions().empty()) {
				nodeB->setOptimumSize(nodeB->getSizeOptions().front());
			}
			else {
				nodeB->setOptimumSize(defaultSize);
			}
		}
		if (cutType == Node::HORIZONTAL_CUT) {
			double length = max(nodeA->getOptimumSize().getLength(), nodeB->getOptimumSize().getLength());
			double width = nodeA->getOptimumSize().getWidth() + nodeB->getOptimumSize().getWidth();
			Size s(length, width);
			parent->setOptimumSize(s);
		}
		else {
			if (cutType == Node::VERTICAL_CUT) {
				double length = nodeA->getOptimumSize().getLength() + nodeB->getOptimumSize().getLength();
				double width = max(nodeA->getOptimumSize().getWidth(), nodeB->getOptimumSize().getWidth());
				Size s(length, width);
				parent->setOptimumSize(s);
			}
			else {
				//TODO: Throw exception
				cout << "Invalid Cut";
				parent = NULL;
			}
		}
		return sizeNode(parent);
	}
	return;
}
//Utility function to check the working of fastMove(). Converts the tree to root expression form
void Floorplanner::treeToPolish(Node* root, vector<string>& reverseExpression) {
	if (root != NULL) {
		if (root->isEndNode()) {
			reverseExpression.push_back(root->getId());
			return;
			//;
		}
		else {
			if (root->getCutType() == 1) {
				reverseExpression.push_back("|") ;
			}
			if (root->getCutType() == 2) {
				reverseExpression.push_back("-");
			}
			treeToPolish(root->getLeft(),reverseExpression);
			treeToPolish(root->getRight(),reverseExpression);
		}
	}
	return;
}
