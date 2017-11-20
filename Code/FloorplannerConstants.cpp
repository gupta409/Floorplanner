#include "FloorplannerConstants.hpp"
#include "IOUtilites.hpp"
#include "string"
#include "unordered_map"
FloorplannerConstants::FloorplannerConstants()
{
	loadConstants();
}
void FloorplannerConstants::loadConstants() {
	///Load data from config file
	unordered_map<string,double> data;
	data = IOUtilites::getInstance().readConfigData();
	if(data.find("coolDownRate")!= data.end()){
		coolDownRate = data.find("coolDownRate")->second;
	}else{
		coolDownRate = 0.90;
	}
	if(data.find("startTemperature")!= data.end()){
		startTemperature = data.find("startTemperature")->second;
	}else{
		startTemperature = 5000;
	}
	if(data.find("freezingTemperature")!= data.end()){
		freezingTemperature = data.find("freezingTemperature")->second;
	}else{
		freezingTemperature = 0.1;
	}
	if(data.find("movesCoolDown")!= data.end()){
		movesCoolDown = data.find("movesCoolDown")->second;
	}else{
		movesCoolDown = 0.95;
	}
	if(data.find("movesPerStep")!= data.end()){
		movesPerStep = data.find("movesPerStep")->second;
	}else{
		movesPerStep = 500;
	}
}
double FloorplannerConstants::getMovesCoolDown() {
	return movesCoolDown;
}
double FloorplannerConstants::getCoolDownRate() {
	return coolDownRate;
}
double FloorplannerConstants::getFreezingTemperature() {
	return freezingTemperature;
}
double FloorplannerConstants::getBoltzmanConstant() {
	return boltzmanConstant;
}
double FloorplannerConstants::getStartTemp() {
	return startTemperature;
}
int FloorplannerConstants::getMovesPerStep() {
	return movesPerStep;
}
