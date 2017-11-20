/*ode.h
 * IOUtilites.hpp
 *
 *  Created on: Nov 5, 2017
 *      Author: Anish Gupta
 */

#ifndef IOUTILITES_HPP_
#define IOUTILITES_HPP_
#include "vector"
#include <unordered_map>
#include <fstream>
#include <regex>
#include "Node.hpp"
void IOUtilitiesTest();
class IOUtilites {
private:
	string inputFile;
	string outputFile;
	string dumpFile;
	string configFile;
	ifstream input;
	ifstream configStream;
	ofstream output;
	ofstream dumpStream;
	void steupConnection();
	void closeConnection();
	IOUtilites();
	virtual ~IOUtilites();
public:
	std::list<Node> readData();
	void writeData(unordered_map<string, Node*> nodes, double totalArea, double blackArea);
	void dumpData(string data);
	std::unordered_map<string, double> readConfigData();
	//Making class singleton
	static IOUtilites& getInstance()
	{
		static IOUtilites instance;
		return instance;
	}
	IOUtilites(IOUtilites const&) = delete;
	void operator=(IOUtilites const&) = delete;
};

#endif /* IOUTILITES_HPP_ */
