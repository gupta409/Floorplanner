/*
 * IOUtilites.hpp
 *
 *  Created on: Nov 5, 2017
 *      Author: Anish Gupta
 */

#ifndef IOUTILITES_HPP_
#define IOUTILITES_HPP_
#include "vector"
#include <fstream>
#include <regex>
#include "Node.hpp"
void IOUtilitiesTest();
class IOUtilites {
private:
	string inputFile;
	string outputFile;
	ifstream input;
	ofstream output;
	void steupConnection();
	void closeConnection();
	IOUtilites();
	virtual ~IOUtilites();
public:
	std::list<Node> readData();
	void writeData();
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
