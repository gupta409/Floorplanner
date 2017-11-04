#include "PolishUtilities.hpp"
#include <string>
#include "iostream"
using namespace std;
void polishUnitTest1();
void polishUnitTest2();
void polishUnitTest3();
void polishUnitTest4();
void printVector(vector<int> data);
void polishUtilitesUnitTest(){
	//polishUnitTest1();
	//polishUnitTest2();
	//polishUnitTest3();
	polishUnitTest4();
}
void polishUnitTest1(){
	string s1 = "|";
	cout<<" Input:\t"<<s1<<" TestName:isHorizontalCut(s1)\t"<<" Result:\t"<<PolishUtilities::isHorizontalCut(s1)<<endl;
	cout<<" Input:\t"<<s1<<" TestName:isVerticalCut(s1)\t"<<" Result:\t"<<PolishUtilities::isVerticalCut(s1)<<endl;
	cout<<" Input:\t"<<s1<<" TestName:isValidCut(s1)\t"<<" Result:\t"<<PolishUtilities::isValidCut(s1)<<endl;
	s1 = "+";
	cout<<" Input:\t"<<s1<<" TestName:isHorizontalCut(s1)\t"<<" Result:\t"<<PolishUtilities::isHorizontalCut(s1)<<endl;
	cout<<" Input:\t"<<s1<<" TestName:isVerticalCut(s1)\t"<<" Result:\t"<<PolishUtilities::isVerticalCut(s1)<<endl;
	cout<<" Input:\t"<<s1<<" TestName:isValidCut(s1)\t"<<" Result:\t"<<PolishUtilities::isValidCut(s1)<<endl;
	s1 = "-";
	cout<<" Input:\t"<<s1<<" TestName:isHorizontalCut(s1)\t"<<" Result:\t"<<PolishUtilities::isHorizontalCut(s1)<<endl;
	cout<<" Input:\t"<<s1<<" TestName:isVerticalCut(s1)\t"<<" Result:\t"<<PolishUtilities::isVerticalCut(s1)<<endl;
	cout<<" Input:\t"<<s1<<" TestName:isValidCut(s1)\t"<<" Result:\t"<<PolishUtilities::isValidCut(s1)<<endl;
}
void polishUnitTest2(){
	vector<std::string> expression;
	expression.push_back("Josh");
	PolishUtilities::printExpression(expression);
	cout<<endl<<"Result: "<<PolishUtilities::isValidExpression(expression)<<endl;
	expression.push_back("Anish");
	PolishUtilities::printExpression(expression);
	cout<<endl<<"Result: "<<PolishUtilities::isValidExpression(expression)<<endl;
	expression.push_back("Rahul");
	expression.push_back("|");
	PolishUtilities::printExpression(expression);
	cout<<endl<<"Result: "<<PolishUtilities::isValidExpression(expression)<<endl;
	expression.push_back("Ronald");
	expression.push_back("-");
	PolishUtilities::printExpression(expression);
	cout<<endl<<"Result: "<<PolishUtilities::isValidExpression(expression)<<endl;
	expression.push_back("-");
	PolishUtilities::printExpression(expression);
	cout<<endl<<"Result: "<<PolishUtilities::isValidExpression(expression)<<endl;
}
void polishUnitTest3() {
	vector<std::string> expression;
	expression.push_back("Josh");
	PolishUtilities::printExpression(expression);
	cout << endl << "Result: " << PolishUtilities::isNormalizedExpression(expression) << endl;
	expression.push_back("Anish");
	PolishUtilities::printExpression(expression);
	cout << endl << "Result: " << PolishUtilities::isNormalizedExpression(expression) << endl;
	expression.push_back("Rahul");
	expression.push_back("|");
	PolishUtilities::printExpression(expression);
	cout << endl << "Result: " << PolishUtilities::isNormalizedExpression(expression) << endl;
	expression.push_back("Ronald");
	expression.push_back("-");
	PolishUtilities::printExpression(expression);
	cout << endl << "Result: " << PolishUtilities::isNormalizedExpression(expression) << endl;
	expression.push_back("-");
	PolishUtilities::printExpression(expression);
	cout << endl << "Result: " << PolishUtilities::isNormalizedExpression(expression) << endl;
}
void polishUnitTest4() {
	vector<std::string> expression;
	expression.push_back("Josh");
	expression.push_back("Anish");
	expression.push_back("Rahul");
	expression.push_back("|");
	expression.push_back("Ronald");
	expression.push_back("-");
	expression.push_back("-");
	PolishUtilities::printExpression(expression);
	cout << endl << "Result: " << endl; 
	cout << "Operators: ";
	printVector(PolishUtilities::getLocations(expression).first);
	cout << "\n Operands: ";
	printVector(PolishUtilities::getLocations(expression).second);
}
void printVector(vector<int> data) {
	for (auto it = data.begin(); it != data.end(); ++it) {
		cout << *it;
	}
}
