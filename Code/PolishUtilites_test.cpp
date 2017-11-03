#include "PolishUtilities.hpp"
#include <string>
#include "iostream"
using namespace std;
void unitTest1();
void unitTest2();
void polishUtilitesUnitTest(){
	unitTest1();
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
	expression.push_back("Anish");
	expression.push_back("Rahul");
	expression.push_back("|");
	cout<<PolishUtilities::isValidExpression(expression)<<endl;
	expression.push_back("Ronald");
	expression.push_back("-");
	cout<<PolishUtilities::isValidExpression(expression)<<endl;
}
