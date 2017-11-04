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
			//If two consecutive cuts found
			if (isValidCut(prev) && isValidCut(curr)) {
				isNormalized = false;
				break;
			}
			else {
				prev = curr;
			}
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