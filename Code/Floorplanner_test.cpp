/*
 * Floorplanner_test.cpp
 *
 *  Created on: Nov 1, 2017
 *      Author: Destroyer
 */

#include "Floorplanner.hpp"
#include "list"
#include "Node.hpp"
using namespace std;
void floorplannerUnitTest(){

	list<Size> l1;
	Size s(1,2);
	l1.push_back(s);
	Node n1("hard1",l1);
	Node n2("hard2",l1);
	Node n3("hard3",l1);
	Node n4("hard4",l1);
	list<Node> nodes;
	nodes.push_back(n1);
	nodes.push_back(n2);
	nodes.push_back(n3);
	nodes.push_back(n4);
	for(auto it:nodes){
		//cout<<it.getId()<<"\t"<<" Length:"<<it.getSizeOptions().front().getLength()<<" Width:"<<it.getSizeOptions().front().getWidth()<<endl;
	}
	Floorplanner floorplanner1(nodes);
	//floorplanner1.printNodes();
	floorplanner1.floorplan();
	//floorplanner1.sizeNodes(n1,n2,Node::HORIZONTAL_CUT);
	floorplanner1.printNodes();
	/*
	 *Copy to floorplan function
	int i = 0;
	sizeNodes(*nodes.find("hard2")->second,*nodes.find("hard2")->second,Node::VERTICAL_CUT);
	auto itp = this->nodes.begin();
	++itp;
	printNodes();
	for(auto it = this->nodes.begin();itp != this->nodes.end() && it != this->nodes.end(); ++it, ++itp){
		if(i<5){
			Node* n1 = it->second;

			Node* n2 = it->second;
			sizeNodes(*n1,*n2,Node::VERTICAL_CUT);
					i++;
		}
	}
	 */
}
