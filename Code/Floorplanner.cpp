#include "unordered_map"
#include "Floorplanner.hpp"
#include "PolishUtilities.hpp"
#include "Node.hpp"
#include "algorithm"
#include "stack"
#include "string"
//Finds the optimum size of the Nodes with the specified cut
Node* Floorplanner::sizeNodes(Node& nodeA, Node& nodeB, int cutType) {
	//TODO: Set optimum size based on cut; currently directly using first element of the options: considering only one option for each hard block
	Node* parent;
	list<Size> temp;
	Size defaultSize(0,0);
	//FIXME: Only Size nodeA and nodeB and not all nodes in the map
	if(!nodeA.getSizeOptions().empty()){
		nodeA.setOptimumSize(nodeA.getSizeOptions().front());
	}else{
		nodeA.setOptimumSize(defaultSize);
	}
	if(!nodeB.getSizeOptions().empty()){
		nodeB.setOptimumSize(nodeB.getSizeOptions().front());
	}else{
		nodeB.setOptimumSize(defaultSize);
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
	//TODO:
	return isAccepted;
}
//Makes changes in the polish expression based on the Wong-Liu Moves model
void Floorplanner::move(vector<string>& currentPolish) {
	//ToDO:
}
//Returns new temperature
double Floorplanner::coolDown(double temperature) {
	//TODO:
	return 0.0;
}

Floorplanner::Floorplanner(list<Node>& nodes) {
	for(auto it = nodes.begin(); it!=nodes.end();++it){
		std::pair<string,Node*> new_node(it->getId(),&*it);
		this->nodes.insert(new_node);
	}
}
//FIXME: Bugs in this function
void Floorplanner::floorplan() {
	//TODO: Write Simulated Annealing code here
	vector<string> expression = generateInitialExpression();
	printExpression(expression);
	cout<<"SomethingSOme";
	//Node* root = sizeNodes(*nodes.find("hard4")->second,*nodes.find("hard3")->second,Node::HORIZONTAL_CUT);
	//Node* root = sizeNodes(*nodes.find("hard4")->second,*nodes.find("hard3")->second,Node::VERTICAL_CUT);
	Node* root = polishToTree(expression);
	cout<<"\nArea:\t"<<computeCost(root)<<endl;
	this->printNodes();
}
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
			//TODO: Re-check if second node is not getting added twice
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
void Floorplanner::printExpression(const vector<string>& expression){
	for(auto it = expression.begin();it!=expression.end();++it){
		cout<<*it;
	}
	cout<<endl;
}
