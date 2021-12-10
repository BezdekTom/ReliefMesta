#pragma once
#include <fstream>
#include "ReliefCreator.h"

class BuildingsLoader
{
public:
	/**
	 * Loads data of buildings and adds these buildings to reliefCreator
	 *
	 * \param reliefCreator is the ReliefCreator to add data
	 * \param inputFileName name of the file with data of buildings, in form:  <int begin> <int height> <int end> \n
	 * \return false if it is impossible to add a building to reliefCreator, otherwise it return true
	 */
	static bool loadBuildingsFromFile(ReliefCreator& reliefCreator, const std::string& inputFileName);
};
