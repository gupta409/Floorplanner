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
					if(!isValidCut(polishStack.top())){
						polishStack.pop();
					}else{
						isValid = false;
						break;
					}
				}else{
					isValid = false;
					break;
				}
			}else{
				isValid = false;
				break;
			}
		}
		else{
			//Name block found; add to the stack
			polishStack.push(temp);
		}
	}
	if(!polishStack.empty()){
		isValid = false;
	}
	return isValid;
}
