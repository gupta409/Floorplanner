#include "FloorplannerConstants.hpp"
#include <iostream>
void floorplannerConstantsTest() {
	std::cout << "coolDownRate:\t"<<FloorplannerConstants::getInstance().getCoolDownRate()<<std::endl;
	std::cout << "boltzmanConstant:\t" << FloorplannerConstants::getInstance().getBoltzmanConstant() << std::endl;
	std::cout << "FreezingTemperature:\t" << FloorplannerConstants::getInstance().getFreezingTemperature() << std::endl;
}