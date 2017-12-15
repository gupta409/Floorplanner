//#include "Vertex.hpp"
#include "Edge.hpp"
Edge::Edge() {
	this->source = nullptr;
	this->destination = nullptr;
	this->weight = 0;
}
Edge::Edge(Vertex &source, Vertex &destination, double weight){
	this->source = &source;
	this->destination = &destination;
	this->weight = weight;
}
Vertex * Edge::getSource(){
	return this->source;
}
void Edge::setSource(Vertex & source){
	this->source = &source;
}
Vertex * Edge::getDestination(){
	return this->destination;
}
void Edge::setDestination(Vertex & destination){
	this->destination = &destination;
}
int Edge::getWeight(){
	return this->weight;
}
void Edge::setWeight(int weight){
	this->weight = weight;
}