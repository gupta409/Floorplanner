#pragma once
void floorplannerConstantsTest();
class FloorplannerConstants
{
private:
	void loadConstants();
	FloorplannerConstants();
	//Constants
	double coolDownRate;
	double startTemperature;
	double freezingTemperature;
	double boltzmanConstant;
	int movesPerStep;
	double movesCoolDown;
public:
	//Making class singleton
	static FloorplannerConstants& getInstance()
	{
		static FloorplannerConstants instance;
		return instance;
	}
	FloorplannerConstants(FloorplannerConstants const&) = delete;
	void operator=(FloorplannerConstants const&) = delete;
	double getCoolDownRate();
	double getFreezingTemperature();
	double getBoltzmanConstant();
	double getStartTemp();
	double getMovesCoolDown();
	int getMovesPerStep();
};

