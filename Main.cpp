#include <fstream>
#include <string>
#include <iostream>

#include "ReliefCreater.h"
#include "ReliefPrinter.h"
#include "BuildingsLoader.h"

void manualTests(ReliefCreater& reliefCreater)
{
	reliefCreater.addBuilding(1, 5, 8);
	reliefCreater.addBuilding(2, 6, 8);
	reliefCreater.addBuilding(3, 7, 8);
	reliefCreater.addBuilding(6, 7, 8);
	reliefCreater.addBuilding(6, 12, 8);
	reliefCreater.addBuilding(15, 20, 8);
	reliefCreater.addBuilding(0, 9, 8);
}


int main()
{

	ReliefCreater reliefCreater;
	
	//manualTests(reliefCreater);
	
	BuildingsLoader::loadBuildingsFromFile(reliefCreater, "testData.txt");


	reliefCreater.createRelief();
	const std::vector<int>& relief = reliefCreater.getRelief();

	ReliefPrinter::printRelief(relief, std::cout);

	return 0;
}
