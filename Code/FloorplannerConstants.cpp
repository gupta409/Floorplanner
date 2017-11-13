#include "FloorplannerConstants.hpp"


FloorplannerConstants::FloorplannerConstants()
{
	loadConstants();
}
void FloorplannerConstants::loadConstants() {
	//TODO: load constant form config file
	coolDownRate = 0.90;
	startTemperature = 50;
	freezingTemperature = 0.1;
	boltzmanConstant = 1;
	movesCoolDown = 0.95;
	movesPerStep = 5;
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