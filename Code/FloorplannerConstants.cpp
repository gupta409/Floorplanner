#include "FloorplannerConstants.hpp"


FloorplannerConstants::FloorplannerConstants()
{
	loadConstants();
}
void FloorplannerConstants::loadConstants() {
	//TODO: load constant form config file
	coolDownRate = 0.95;
	startTemperature = 4000000;
	freezingTemperature = 0.1;
	boltzmanConstant = 1;
	movesPerStep = 500;
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