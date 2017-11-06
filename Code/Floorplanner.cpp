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
		//cout <<"r:\t"<<r<<"\tboltz:\t"<< boltz << endl;
		if (r < boltz) {
			isAccepted = true;
		}
	}
	/*if (isAccepted) {
		cout << "Accepted"<<endl;
	}
	else {
		cout << "Rejected"<<endl;
	}*/
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
}

//Simulated Annealing performed here
void Floorplanner::floorplan() {
	vector<string> currentExpression = generateInitialExpression();
	double temperature = FloorplannerConstants::getInstance().getStartTemp();
	Node* root;
	double delCost, newCost, currentCost;
	currentCost = computeCost(polishToTree(currentExpression));
	//cout << "Orignal Cost:" << currentCost<<endl;
	vector<string> newExpression;
	while(temperature > FloorplannerConstants::getInstance().getFreezingTemperature()){
		for (int i = 1; i <= FloorplannerConstants::getInstance().getMovesPerStep(); i++) {
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
	}
	cout << computeCost(polishToTree(currentExpression))<<endl;
}

//Prints sizing of all the nodes in the tree
void Floorplanner::printNodes(){
	for(auto it = this->nodes.begin(); it != this->nodes.end(); ++it){
		cout<<"ID:\t"<<it->first<<" Length:\t"<<it->second->getOptimumSize().getLength()<<" Width:\t"<<it->second->getOptimumSize().getWidth()<<endl;
	}
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
