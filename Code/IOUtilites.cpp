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
	dumpStream.open(dumpFile);
	configStream.open(configFile);
}
void IOUtilites::closeConnection() {
	if (input.is_open()) {
		input.close();
	}
	if (output.is_open()) {
		output.close();
	}
	if (dumpStream.is_open()) {
		dumpStream.close();
	}
	if (configStream.is_open()) {
		configStream.close();
	}
}
IOUtilites::IOUtilites() {
	//Get input file name
	std::cout<<"Enter the input file name: ";
	//std::cin>>inputFile;
	inputFile = "n10hard.blocks";
	string temp = "";
	std::regex fileName("[\\w\\d]+");
	std::smatch match;
	//Make output file name
	if (std::regex_search(inputFile, match, fileName)) {
		temp = match.str();
		outputFile = temp + ".out";
	}else{
		outputFile = "output.out";
	}
	dumpFile = temp +"dump.csv";
	configFile = "constants.cfg";
	steupConnection();
}
IOUtilites::~IOUtilites() {
	closeConnection();
}

std::list<Node> IOUtilites::readData()
{
	const string HARD_CORDS_REGEX = "(\\d+(?=\\,\\s))|(\\d+(?=\\)))";
	const string SOFT_CORDS_REGEX = "[\\d.\\d]+";
	const string NAME_REGEX = "[a-zA-Z]+[a-zA-Z\\d]+";
	const string INVALID = "Invalid";
	const string HARDBLOCKID = "hardrectilinear";
	const string SOFTBLOCKID = "softrectangular";
	std::list<Node> returnData;
	std::unordered_map<string,Node> data;
	string tempLine;
	string blockType = "Invalid";
	string tempId = "Invalid";
	double tempLength, tempWidth;
	vector<double> xcords, ycords;
	std::regex namesExpression(NAME_REGEX);
	std::smatch match;
	if (input.good()) {
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
				std::regex cordsExpression(HARD_CORDS_REGEX);
				int i = 0;
				while (std::regex_search(tempLine, match, cordsExpression)) {
					if (i % 2 == 0) {
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
					list<Size> options;
					options.push_back(s);
					Size s90(tempWidth, tempLength);
					options.push_back(s90);
					//Looks for node with same name if already not present
					if (data.find(tempId) == data.end()) {
						Node n(tempId, options);
						data.insert(pair<string, Node>(tempId, n));
					}
					else {
						//Node with same Id is present. Append to options
						data.find(tempId)->second.getSizeOptions().push_back(s);
						data.find(tempId)->second.getSizeOptions().push_back(s90);
					}
				}
			}
			if (blockType.compare(INVALID) != 0 && blockType.compare(SOFTBLOCKID) == 0) {
				//Create soft block
				std::regex cordsExpression(SOFT_CORDS_REGEX);
				double area;
				double minRatio;
				double maxRatio;
				//std::regex_search(tempLine, match, cordsExpression);
				//Area:
				if (std::regex_search(tempLine, match, cordsExpression)) {
					area = std::stod(match.str());
					tempLine = match.suffix().str();
				}
				//Min Aspect Ratio:
				if (std::regex_search(tempLine, match, cordsExpression)) {
					minRatio = std::stod(match.str());
					tempLine = match.suffix().str();
				}
				//Max Aspect Ratio:
				if (std::regex_search(tempLine, match, cordsExpression)) {
					maxRatio = std::stod(match.str());
					tempLine = match.suffix().str();
				}
				//Add to map
				if (data.find(tempId) == data.end()) {
					Node n(tempId, area, minRatio, maxRatio);
					data.insert(pair<string, Node>(tempId, n));
				}
				else {
					//FIXME: Some error here
					//Node with same Id is present. Append to options
					//cout << "Malforamtted Input file. Duplicate soft node found";
				}
			}
			xcords.clear();
			ycords.clear();
		}
	}
	else {
		cout << "File not found. Stream not setup" << endl;
	}
	for (auto it : data) {
		returnData.push_back(it.second);
	}
	return returnData;
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
void IOUtilites::dumpData(string data){
	dumpStream<<data;
}
unordered_map<string, double> IOUtilites::readConfigData(){
	unordered_map<string, double> data;
	const string KEY_REGEX = "[a-z]\\w+";
	const string VALUE_REGEX = "[\\d.\\d]+";
	string tempLine;
	string tempKey;
	double tempValue;
	vector<double> xcords, ycords;
	std::regex KEY(KEY_REGEX);
	std::regex VALUE(VALUE_REGEX);
	std::smatch match;
	if (configStream.good()) {
		while (std::getline(configStream, tempLine)) {
			if (std::regex_search(tempLine, match, KEY)) {
				tempKey = match.str();
				tempLine = match.suffix().str();
				if (std::regex_search(tempLine, match, VALUE)) {
					tempValue = std::stod(match.str());
					tempLine = match.suffix().str();
					data.insert(std::pair<string, double>(tempKey, tempValue));
				}
			}
		}
	}
	else {
		cout << "External Config file not found. Using default configurations."<<endl;
	}
	return data;
}
