#include "FloorplannerConstants.hpp"


FloorplannerConstants::FloorplannerConstants()
{
	loadConstants();
}
void FloorplannerConstants::loadConstants() {
	//TODO: load constant form config file
	coolDownRate = 0.95;
	startTemperature = 40000;
	freezingTemperature = 0.01;
	boltzmanConstant = 1;
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