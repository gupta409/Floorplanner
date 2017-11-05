#include "Node.hpp"
#include "PolishUtilities.hpp"
#include "stack"
#include "vector"
using namespace std;

const string PolishUtilities::VERTICAL_CUT = "|";
const string PolishUtilities::HORIZONTAL_CUT = "-";
PolishUtilities::PolishUtilities() {
}
bool PolishUtilities::isVerticalCut(string s){
	if(s.compare(VERTICAL_CUT)==0)
		return true;
	else
		return false;
}
bool PolishUtilities::isHorizontalCut(string s){
	if(s.compare(HORIZONTAL_CUT)==0)
		return true;
	else
		return false;
}
bool PolishUtilities::isValidCut(string s){
	if(isHorizontalCut(s)||isVerticalCut(s))
		return true;
	else
		return false;
}
int PolishUtilities::getCutType(string s){
	if(isHorizontalCut(s)){
		return Node::HORIZONTAL_CUT;
	}if(isVerticalCut(s)){
		return Node::VERTICAL_CUT;
	}else{
		//TODO: Throw exception of invalid cut type
		return 3;
	}
}
bool PolishUtilities::isValidExpression(const vector<string>& experssion){
	stack<string> polishStack;
	string temp;
	bool isValid = true;
	for(unsigned int i=0;i<experssion.size();i++){
		temp = experssion[i];
		//When cut found the next two in stack should be operands
		if(PolishUtilities::isValidCut(temp)){
			if(!polishStack.empty()){
				if(!isValidCut(polishStack.top())){
					polishStack.pop();
					if(!polishStack.empty()){
						if(!isValidCut(polishStack.top())){
							//Not performing pop to simulate keeping computed variable in the top again
							//polishStack.pop();
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
					//Operator fetched from stack instread of operand, eg: "||"
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
		isValid = false;
	}
	return isValid;
}
bool PolishUtilities::isNormalizedExpression(const vector<string>& expression) {
	bool isNormalized = true;
	string prev, curr;
	if (isValidExpression(expression)) {
		auto it = expression.begin();
		prev = *it;
		if (it != expression.end()) {
			++it;
		}
		else {
			isNormalized = true;
		}
		for (; it != expression.end(); ++it) {
			curr = *it;
			//If two consecutive horizontal cuts found
			if (isHorizontalCut(prev) && isHorizontalCut(curr)) {
				isNormalized = false;
				break;
			}
			//If two consecutive vertical cuts found
			if (isVerticalCut(prev) && isVerticalCut(curr)) {
				isNormalized = false;
				break;
			}
			prev = curr;
		}
	}
	else {
		isNormalized = false;
	}
	return isNormalized;
}
void PolishUtilities::printExpression(const vector<string>& expression) {
	for (auto it = expression.begin(); it != expression.end(); ++it) {
		cout << *it;
	}
}
//Returns indexs where operand is present and where operator is present <<vector of operands>,<vecotr of operators>>
pair<vector<int>, vector<int>> PolishUtilities::getLocations(const vector<string>& expression) {
	pair<vector<int>, vector<int>>  data;
	int i = 0;
	for (int i = 0; i < expression.size();i++) {
		string temp = expression.at(i);
		if (isValidCut(temp)) {
			//Add to list of Operators
			data.first.push_back(i);
		}
		else {
			//Add to list of Operands
			data.second.push_back(i);
		}
	}
	//Returns operators,operand index pair
	return data;
}
//Returns pair of starting and ending points of indexes where consecutive operators are found between operands
vector<pair<int, int>> PolishUtilities::getRepOperators(const vector<string>& expression)
{
	vector<pair<int, int>> locations;
	int start = 0;
	int end = 0;
	bool isStarted = false;
	bool isStopped = true;
	for (int i = 0; i < expression.size();i++) {
		if (!isStarted && isValidCut(expression[i])) {
			isStarted = true;
			start = i;
		}
		if (isStarted && !isValidCut(expression[i])) {
			isStarted = false;
			end = i - 1;
			locations.push_back(pair<int, int>(start, end));
		}
			
		
	}
	return locations;
}
//Returns compliment of the cut
string PolishUtilities::getCompliment(string s) {
	if (isValidCut(s)) {
		if (isHorizontalCut(s)) {
			return VERTICAL_CUT;
		}
		else {
			return HORIZONTAL_CUT;
		}
	}
	else {
		//FIXME: Throw invalid cut exception
		cout << "Invalid Cut provieded for compliemnt";
		return HORIZONTAL_CUT;
	}
}
//Returns indexes of operands which can be exchanged with next operator for valid expression
vector<int> PolishUtilities::getSurroundedOperands(const vector<string>& expression) {
	//Look for operands
	//If found check for operator on either side
		//If found on both sides check if both are not same ->true
		//If found on one side ->true
	vector<int> validIndices;
	stack<string> validatorStack;
	for (int i = 0; i < expression.size(); i++) {
		//if operand found
		if (!isValidCut(expression[i])) {
			validatorStack.push(expression[i]);
			//if i is not last element in the expression and i+1 is a valid cut and if the stack size is >=3
			if (i < expression.size() - 1 && isValidCut(expression[i+1]) && validatorStack.size() >= 3) {
				// and the previous element is not the same cut
				if (expression[i+1].compare(expression[i-1]) != 0) {
					validIndices.push_back(i);
				}
			}
		}
		else {
			//Cut found reduce the stack size to simulate operation being performed
			validatorStack.pop();
			//Checking if it can be exchanged with the next operand 
			if (i < expression.size() - 2) {
				//Next value is an operand and next to next is the same not operator as the current operator
				if (!isValidCut(expression[i + 1]) && expression[i].compare(expression[i + 2]) != 0) {
					validIndices.push_back(i);
				}
			}
		}
	}
	return validIndices;
}