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
		isValid = false;
	}
	return isValid;
}
