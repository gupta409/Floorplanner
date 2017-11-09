/*
 * IOUtilites.cpp
 *
 *  Created on: Nov 5, 2017
 *      Author: Anish Gupta
 */

#include "IOUtilites.hpp"
#include "Size.hpp"
#include <istream>
#include <string>
#include <regex>
void IOUtilites::steupConnection(){
	input.open(inputFile);
	output.open(outputFile);
}
void IOUtilites::closeConnection() {
	if (input.is_open()) {
		input.close();
	}
	if (output.is_open()) {
		output.close();
	}
}
IOUtilites::IOUtilites() {
	inputFile = "input.txt";
	outputFile = "output.txt";
	steupConnection();
}
IOUtilites::~IOUtilites() {
	closeConnection();
}

std::list<Node> IOUtilites::readData()
{
	const string HARD_CORDS_REGEX = "(\\d+(?=\\,\\s))|(\\d+(?=\\)))";
	const string NAME_REGEX = "[a-zA-Z]+[a-zA-Z\\d]+";
	const string INVALID = "Invalid";
	const string HARDBLOCKID = "hardrectilinear";
	std::list<Node> data;
	string tempLine;
	string blockType = "Invalid";
	string tempId = "Invalid";
	double tempLength, tempWidth;
	vector<double> xcords, ycords;
	std::regex cordsExpression(HARD_CORDS_REGEX);
	std::regex namesExpression(NAME_REGEX);
	std::smatch match;
	while (std::getline(input, tempLine)) {
		if (std::regex_search(tempLine, match, namesExpression)) {
			tempId = match.str();
			tempLine = match.suffix().str();
		}
		if (std::regex_search(tempLine, match, namesExpression)) {
			blockType = match.str();
			tempLine = match.suffix().str();
		}
		if (blockType.compare(INVALID) != 0 && blockType.compare(HARDBLOCKID) == 0) {
			//Create hard block
			int i = 0;
			while (std::regex_search(tempLine, match, cordsExpression)) {
				if (i % 2 ==0) {
					xcords.push_back(std::stod(match.str()));
				}
				else {
					ycords.push_back(std::stod(match.str()));
				}
				i++;
				tempLine = match.suffix().str();
			}
			if (i > 0) {
				tempLength = *max_element(std::begin(xcords), std::end(xcords)) - *min_element(std::begin(xcords), std::end(xcords));
				tempWidth = *max_element(std::begin(ycords), std::end(ycords)) - *min_element(std::begin(ycords), std::end(ycords));
				Size s(tempLength, tempWidth);
				//TODO: Future scope: Make new node only if node with same name is not found before else add size option to node
				list<Size> options;
				options.push_back(s);
				//FIXME: Potential bug here
				Node n(tempId, options);
				data.push_back(n);
			}
		}
		xcords.clear();
		ycords.clear();
	}
	return data;
}
void IOUtilites::writeData(unordered_map<string, Node*> nodes, double totalArea, double blackArea) {
	output << "Final area = " << totalArea << endl;
	output << "Black area = " << blackArea << endl;
	output << endl;
	output << "block_name lower_left(x,y)coordinate upper_right(x,y)coordinate"<<endl;
	//Print node data
	for (auto it:nodes) {
		output << it.second->getId() << " (" << it.second->getLLCord().first << "," << it.second->getLLCord().second << ") " << "(" << it.second->getURCord().first << "," << it.second->getURCord().second << ")"<<endl;
	}
}