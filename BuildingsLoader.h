#pragma once
#include <fstream>
#include "ReliefCreater.h"

class BuildingsLoader
{
public:
	/**
	 * Method load data about buildings and add these building to reliefCreater
	 * 
	 * \param reliefCreater is the reliefCreater in which are the data added
	 * \param inputFileName name of file with data about building, in form:  <int begin> <int height> <int end> \n 
	 * \return false if its imposible to add the building to reliefCreater, otherwise it return true
	 */
	static bool loadBuildingsFromFile(ReliefCreater& reliefCreater, const std::string& inputFileName);
};

