#include "PolishUtilities.hpp"
#include <string>
#include "iostream"
using namespace std;
void unitTest1();
void unitTest2();
void printExpression(const vector<string>& expression);
void polishUtilitesUnitTest(){
	//unitTest1();
	unitTest2();
}
void unitTest1(){
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
void unitTest2(){
	vector<std::string> expression;
	expression.push_back("Josh");
	printExpression(expression);
	cout<<endl<<"Result: "<<PolishUtilities::isValidExpression(expression)<<endl;
	expression.push_back("Anish");
	printExpression(expression);
	cout<<endl<<"Result: "<<PolishUtilities::isValidExpression(expression)<<endl;
	expression.push_back("Rahul");
	expression.push_back("|");
	printExpression(expression);
	cout<<endl<<"Result: "<<PolishUtilities::isValidExpression(expression)<<endl;
	expression.push_back("Ronald");
	expression.push_back("-");
	printExpression(expression);
	cout<<endl<<"Result: "<<PolishUtilities::isValidExpression(expression)<<endl;
	expression.push_back("-");
	printExpression(expression);
	cout<<endl<<"Result: "<<PolishUtilities::isValidExpression(expression)<<endl;
}
void printExpression(const vector<string>& expression){
	for(auto it = expression.begin(); it != expression.end(); ++it){
		cout<<*it;
	}
}
