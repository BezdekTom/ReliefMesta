#include <fstream>
#include <string>
#include <iostream>

#include "ReliefCreator.h"
#include "ReliefPrinter.h"
#include "BuildingsLoader.h"

void manualTests(ReliefCreator& reliefCreator)
{
	reliefCreator.addBuilding(1, 8, 7);
	reliefCreator.addBuilding(6, 8, 9);
}


int main()
{

	ReliefCreator reliefCreator;

	//manualTests(reliefCreator);

	BuildingsLoader::loadBuildingsFromFile(reliefCreator, "testData.txt");


	reliefCreator.createRelief();
	const std::vector<int>& relief = reliefCreator.getRelief();

	ReliefPrinter::printRelief(relief, std::cout);

	return 0;
}
